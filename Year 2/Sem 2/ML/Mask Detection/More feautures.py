#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pyplot as plt
import numpy as np
import librosa
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


# In[6]:


X_train, y_train = [], []
signals_gen_train = get_signals(train_df, train_path)

for signal, label in signals_gen_train:
    sample1 = librosa.feature.mfcc(signal, sr=sample_rate)
    sample2 = get_fft(signal)
    sample1 = librosa.util.normalize(sample1).reshape(-1)
    sample = list(sample1) + list(sample2)
    X_train.append(sample)
    y_train.append(label)

X_train, y_train = np.array(X_train), np.array(y_train)


# In[7]:


X_val, y_val = [], []
signals_gen_val = get_signals(validation_df, validation_path)

for signal, label in signals_gen_val:
    sample1 = librosa.feature.mfcc(signal, sr=sample_rate)
    sample2 = get_fft(signal)
    sample1 = librosa.util.normalize(sample1).reshape(-1)
    sample = list(sample1) + list(sample2)
    X_val.append(sample)
    y_val.append(label)

X_val, y_val = np.array(X_val), np.array(y_val)


# In[46]:


bst = xgb.XGBClassifier(objective='binary:logistic', gamma=0.1, max_depth=4)
bst.fit(X_train, y_train)


# In[47]:


bst.score(X_val, y_val)


# xgboost cu mfcc si fft: 72.2%

# In[8]:


test_path = 'test/test/'
test_df = pd.read_csv('test.txt', header=None)
test_df.columns = ['sample']
test_df['label'] = [1] * len(test_df)  # doar ca sa pot folosi aceeasi functie de get_signals

X_test = []
signals_gen_test = get_signals(test_df, test_path)

for signal, label in signals_gen_test:
    sample1 = librosa.feature.mfcc(signal, sr=sample_rate)
    sample2 = get_fft(signal)
    sample1 = librosa.util.normalize(sample1).reshape(-1)
    sample = list(sample1) + list(sample2)
    X_test.append(sample)

X_test = np.array(X_test)


# In[9]:


def salvare_predictii(y_pred, nume_model):
    test_df['label'] = y_pred

    with open('predictions_' + nume_model + '.txt', 'w') as fout:
        fout.write('name,label\n')
        for index, [sample, label] in test_df.iterrows():
            fout.write(str(sample))
            fout.write(',')
            fout.write(str(label))
            fout.write('\n')


# In[48]:


y_pred = bst.predict(X_test)
salvare_predictii(y_pred, 'xgb_mfcc_fft_g01_md4')


# In[72]:


X_train_more = []
signals_gen_train = get_signals(train_df, train_path)

i = 0
for signal, label in tqdm(signals_gen_train):
    melspec = librosa.feature.melspectrogram(signal, sr=sample_rate)
    chroma = librosa.feature.chroma_cqt(signal, sr=sample_rate)
    sample = list(melspec.reshape(-1)) + list(chroma.reshape(-1)) + list(X_train[i])
    X_train_more.append(sample)
    i += 1

X_train_more = np.array(X_train_more)


# In[73]:


X_val_more = []
signals_gen_val = get_signals(validation_df, validation_path)

i = 0
for signal, label in tqdm(signals_gen_val):
    melspec = librosa.feature.melspectrogram(signal, sr=sample_rate)
    chroma = librosa.feature.chroma_cqt(signal, sr=sample_rate)
    sample = list(melspec.reshape(-1)) + list(chroma.reshape(-1)) + list(X_val[i])
    X_val_more.append(sample)
    i += 1

X_val_more = np.array(X_val_more)


# In[77]:


X_test_more = []
signals_gen_test = get_signals(test_df, test_path)

i = 0
for signal, label in signals_gen_test:
    melspec = librosa.feature.melspectrogram(signal, sr=sample_rate)
    chroma = librosa.feature.chroma_cqt(signal, sr=sample_rate)
    sample = list(melspec.reshape(-1)) + list(chroma.reshape(-1)) + list(X_test[i])
    X_test_more.append(sample)
    i += 1

X_test_more = np.array(X_test_more)


# In[78]:


bst_more = xgb.XGBClassifier(objective='binary:logistic')
bst_more.fit(X_train_more, y_train)


# In[80]:


bst_more.score(X_val_more, y_val)


# In[81]:


y_pred = bst_more.predict(X_test_more)
salvare_predictii(y_pred, 'xgb_more')


# In[12]:


X_train_val = list(X_train)
for x in X_val:
    X_train_val.append(list(x))

y_train_val = list(y_train)

for y in y_val:
    y_train_val.append(y)

X_train_val, y_train_val = np.array(X_train_val), np.array(y_train_val)


# In[16]:


bst_all = xgb.XGBClassifier(objective='binary:logistic')
bst_all.fit(X_train_val, y_train_val)


# In[17]:


y_pred = bst_all.predict(X_test)
salvare_predictii(y_pred, 'xgb_all')

