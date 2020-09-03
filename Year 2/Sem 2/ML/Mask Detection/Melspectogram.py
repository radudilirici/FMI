#!/usr/bin/env python
# coding: utf-8

# In[14]:


import matplotlib.pyplot as plt
import numpy as np
import librosa
from librosa.display import specshow
import os
import pandas as pd
from scipy.io import wavfile
from itertools import islice
import xgboost as xgb
from tqdm import tqdm

import keras
from keras.utils import to_categorical
from keras.models import Sequential
from keras.layers import Dense, Dropout, Conv2D, Conv1D, MaxPool2D, MaxPool1D, Flatten, LSTM, TimeDistributed, BatchNormalization, GlobalAveragePooling2D
from keras.metrics import categorical_accuracy


# In[2]:


train_path = 'train/train/'
sample_rate, _ = wavfile.read('train/train/100001.wav')
print(f'sample rate: {sample_rate}')


# In[3]:


train_df = pd.read_csv('train.txt', header=None)
train_df.columns = ['sample', 'label']
train_df.head()


# In[4]:


validation_path = 'validation/validation/'
validation_df = pd.read_csv('validation.txt', header=None)
validation_df.columns = ['sample', 'label']
validation_df.head()


# In[5]:


def get_signals(df, path, sr=sample_rate):
    for index, row in df.iterrows():
        file_name = os.path.join(path, row['sample'])
        yield librosa.load(file_name, sr=sr)[0], row['label']
        
def get_signals_like_label(df, path, signal_label, sr=sample_rate):
    signals = get_signals(df, path, sr)
    for signal, label in signals:
        if label == signal_label:
            yield signal, label

def get_fft(sample, sr=sample_rate):
    fft = abs(np.fft.rfft(sample)/len(sample))
    return fft


# In[28]:


def salvare_predictii(y_pred, nume_model):
    test_df['label'] = y_pred

    with open('predictions_' + nume_model + '.txt', 'w') as fout:
        fout.write('name,label\n')
        for index, [sample, label] in test_df.iterrows():
            fout.write(str(sample))
            fout.write(',')
            fout.write(str(label))
            fout.write('\n')


# In[19]:


X_train, y_train = [], []
signals_gen_train = get_signals(train_df, train_path)

for signal, label in tqdm(signals_gen_train):
    sample = librosa.feature.melspectrogram(signal, sr=sample_rate).T
    X_train.append(sample)
    y_train.append(label)

X_train, y_train = np.array(X_train), np.array(y_train)


# In[20]:


X_val, y_val = [], []
signals_gen_val = get_signals(validation_df, validation_path)

for signal, label in tqdm(signals_gen_val):
    sample = librosa.feature.melspectrogram(signal, sr=sample_rate).T
    X_val.append(sample)
    y_val.append(label)

X_val, y_val = np.array(X_val), np.array(y_val)


# In[21]:


test_path = 'test/test/'
test_df = pd.read_csv('test.txt', header=None)
test_df.columns = ['sample']
test_df['label'] = [1] * len(test_df)  # doar ca sa pot folosi aceeasi functie de get_signals

X_test = []
signals_gen_test = get_signals(test_df, test_path)

for signal, label in tqdm(signals_gen_test):
    sample = librosa.feature.melspectrogram(signal, sr=sample_rate).T
    X_test.append(sample)

X_test = np.array(X_test)


# In[22]:


X_train_cnn = X_train.reshape(X_train.shape[0], X_train.shape[1], X_train.shape[2], 1)
y_train_categ = to_categorical(y_train, 2)

X_train_cnn.shape


# In[23]:


cnn = Sequential()
cnn.add(Conv2D(16, (3, 3), activation='relu', strides=(1, 1), padding='same', input_shape=X_train_cnn.shape[1:]))
cnn.add(Conv2D(32, (3, 3), activation='relu', strides=(1, 1), padding='same'))
cnn.add(Conv2D(64, (3, 3), activation='relu', strides=(1, 1), padding='same'))
cnn.add(Conv2D(128, (3, 3), activation='relu', strides=(1, 1), padding='same'))
cnn.add(MaxPool2D((2, 2)))
cnn.add(Dropout(0.5))
cnn.add(Flatten())
cnn.add(Dense(128, activation='relu'))
cnn.add(Dropout(0.5))
cnn.add(Dense(64, activation='relu'))
cnn.add(Dense(16, activation='relu'))
cnn.add(Dense(8, activation='relu'))
cnn.add(Dense(2, activation='softmax'))
cnn.summary()
cnn.compile(loss='binary_crossentropy', optimizer='adam', metrics=[categorical_accuracy])


# In[24]:


cnn.fit(X_train_cnn, y_train_categ, epochs=20, batch_size=128, validation_split=0.1, shuffle=True)


# L-am oprit manual pentru ca parea ca face overfitting.

# In[25]:


X_val_cnn = X_val.reshape(X_val.shape[0], X_val.shape[1], X_val.shape[2], 1)
y_val_categ = to_categorical(y_val, 2)


# In[26]:


cnn.evaluate(X_val_cnn, y_val_categ)


# In[29]:


X_test_cnn = X_test.reshape(X_test.shape[0], X_test.shape[1], X_test.shape[2], 1)
y_pred_cnn = np.argmax(cnn.predict(X_test_cnn), axis=1)
salvare_predictii(y_pred_cnn, 'cnn_melspectogram')

