#!/usr/bin/env python
# coding: utf-8

# In[36]:


import matplotlib.pyplot as plt
import numpy as np
import librosa
import pandas as pd
import os
from itertools import islice
from scipy.io import wavfile
from python_speech_features import logfbank, mfcc
import keras
from keras.utils import to_categorical
from keras.models import Sequential
from keras.layers import Dense, Dropout, Conv2D, Conv1D, MaxPool2D, MaxPool1D, Flatten, LSTM, TimeDistributed, BatchNormalization, GlobalAveragePooling2D
from keras.metrics import categorical_accuracy
import noisereduce as nr
import xgboost as xgb
from sklearn.model_selection import validation_curve
from sklearn.metrics import confusion_matrix


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


# # Vizualizare date

# In[132]:


true_signals = get_signals_like_label(train_df, train_path, 1)
false_signals = get_signals_like_label(train_df, train_path, 0)
fig, axes = plt.subplots(nrows=2, ncols=5, figsize=(20,8))
fig.suptitle('Signals')

for index, [signal, label] in enumerate(islice(true_signals, 5)):
    axes[0, index  % 5].set_title(label)
    axes[0, index  % 5].plot(signal)
for index, [signal, label] in enumerate(islice(false_signals, 5)):
    axes[1, index  % 5].set_title(label)
    axes[1, index  % 5].plot(signal)
plt.show()


# In[134]:


true_signals = get_signals_like_label(train_df, train_path, 1)
false_signals = get_signals_like_label(train_df, train_path, 0)
fig, axes = plt.subplots(nrows=2, ncols=5, figsize=(20,8))
fig.suptitle('Fourier Transformations')
    
for index, [signal, label] in enumerate(islice(true_signals, 5)):
    fft = get_fft(signal)
    axes[0, index  % 5].set_title(label)
    axes[0, index  % 5].plot(fft)
for index, [signal, label] in enumerate(islice(false_signals, 5)):
    fft = get_fft(signal)
    axes[1, index  % 5].set_title(label)
    axes[1, index  % 5].plot(fft)
plt.show()


# In[185]:


true_signals = get_signals_like_label(train_df, train_path, 1)
false_signals = get_signals_like_label(train_df, train_path, 0)
signals = get_signals(train_df, train_path)
fig, axes = plt.subplots(nrows=4, ncols=3, figsize=(20,10))
fig.suptitle('Banks')
    
for index, [signal, label] in enumerate(islice(true_signals, 6)):
    bank = logfbank(signal, sample_rate).T
    axes[index // 3, index  % 3].set_title(label)
    axes[index // 3, index  % 3].imshow(bank)
for index, [signal, label] in enumerate(islice(false_signals, 6)):
    bank = logfbank(signal, sample_rate).T
    axes[index // 3 + 2, index  % 3].set_title(label)
    axes[index // 3 + 2, index  % 3].imshow(bank)

plt.show()


# In[187]:


true_signals = get_signals_like_label(train_df, train_path, 1)
false_signals = get_signals_like_label(train_df, train_path, 0)
signals = get_signals(train_df, train_path)
fig, axes = plt.subplots(nrows=4, ncols=3, figsize=(20,8))
fig.suptitle('MFCC')
    
for index, [signal, label] in enumerate(islice(true_signals, 6)):
    mfcc_ = mfcc(signal, sample_rate).T
    axes[index // 3, index  % 3].set_title(label)
    axes[index // 3, index  % 3].imshow(mfcc_)
for index, [signal, label] in enumerate(islice(false_signals, 6)):
    mfcc_ = mfcc(signal, sample_rate).T
    axes[index // 3 + 2, index  % 3].set_title(label)
    axes[index // 3 + 2, index  % 3].imshow(mfcc_)

plt.show()


# # Extragere feature-uri

# In[6]:


signals_gen_train = get_signals(train_df, train_path)
means = []

for signal, label in signals_gen_train:
    means.append(np.abs(signal).mean())
means = np.array(means)


# In[7]:


plt.hist(means)


# In[8]:


min_signal = np.argmin(means)
min_signal


# In[9]:


signals_gen_train = get_signals(train_df, train_path)
i = 0

for signal, label in signals_gen_train:
    if i < min_signal:
        i += 1
        continue
    plt.plot(signal)
    break


# In[10]:


mask = (means >= 0.05)
mask[1000:1100]


# In[11]:


X_train, y_train = [], []
signals_gen_train = get_signals(train_df, train_path)

for signal, label in signals_gen_train:
    sample = librosa.feature.mfcc(signal, sr=sample_rate)
    X_train.append(sample)
    y_train.append(label)

X_train = librosa.util.normalize(X_train, axis=1)
y_train = np.array(y_train)


# In[12]:


X_train_flat = X_train.reshape(X_train.shape[0], X_train.shape[1] * X_train.shape[2])


# # Modele
# 
# svc:
# fara masca - 63.3%,
# cu masca - 63.4%
# 
# svc cu masca:
# 
# 64.9% C=10
# 
# 63.4% C=100
# 
# 62.3% C=10, gamma=0.005623413251903491
# 
# logistic regression:
# fara masca - 59.9%,
# cu masca - 60.7%
# 
# mlp:
# fara masca - 64.1%,
# cu masca - 64.8%
# 
# xgboost:
# fara masca - 63.3%,
# cu masca - 63.1%
# 
# xgboost fara masca:
# 
# 64.9% gamma=0.1
# 
# 65.5% gamma=0.1, max_depth=4

# In[13]:


from sklearn.svm import SVC


# In[32]:


svc_model = SVC(C=10)
svc_model.fit(X_train_flat[mask], y_train[mask])


# In[28]:


X_val, y_val = [], []
signals_gen_val = get_signals(validation_df, validation_path)

for signal, label in signals_gen_val:
    sample = librosa.feature.mfcc(signal, sr=sample_rate)
    X_val.append(sample)
    y_val.append(label)

X_val = librosa.util.normalize(X_val, axis=1)
y_val = np.array(y_val)


# In[29]:


X_val_flat = X_val.reshape(X_val.shape[0], X_val.shape[1] * X_val.shape[2])


# In[33]:


svc_model.score(X_val_flat, y_val)


# In[37]:


y_pred_val = svc_model.predict(X_val_flat)
confusion_matrix(y_pred_val, y_val)


# In[14]:


# https://scikit-learn.org/stable/auto_examples/model_selection/plot_validation_curve.html

param_range = np.logspace(-6, -1, 5)
train_scores, test_scores = validation_curve(
    SVC(), X_train_flat, y_train, param_name="gamma", param_range=param_range,
    scoring="accuracy", n_jobs=1)

train_scores_mean = np.mean(train_scores, axis=1)
train_scores_std = np.std(train_scores, axis=1)
test_scores_mean = np.mean(test_scores, axis=1)
test_scores_std = np.std(test_scores, axis=1)

plt.title("Validation Curve with SVM")
plt.xlabel(r"$\gamma$")
plt.ylabel("Score")
plt.ylim(0.0, 1.1)
lw = 2
plt.semilogx(param_range, train_scores_mean, label="Training score",
             color="darkorange", lw=lw)
plt.fill_between(param_range, train_scores_mean - train_scores_std,
                 train_scores_mean + train_scores_std, alpha=0.2,
                 color="darkorange", lw=lw)
plt.semilogx(param_range, test_scores_mean, label="Cross-validation score",
             color="navy", lw=lw)
plt.fill_between(param_range, test_scores_mean - test_scores_std,
                 test_scores_mean + test_scores_std, alpha=0.2,
                 color="navy", lw=lw)
plt.legend(loc="best")
plt.show()


# In jurul lui 10^-2 pare ca e cel mai bun rezultat. La stanga, scorul este mai mic, iar la dreapta diferenta dintre training si validation este prea mare, ceea ce probabil inseamna ca modelul face overfitting.

# In[20]:


param_range


# In[25]:


svc_model = SVC(C=10, gamma=param_range[3])
svc_model.fit(X_train_flat[mask], y_train[mask])


# In[30]:


svc_model.score(X_val_flat, y_val)


# nvm

# In[34]:


test_path = 'test/test/'
test_df = pd.read_csv('test.txt', header=None)
test_df.columns = ['sample']
test_df['label'] = [1] * len(test_df)  # doar ca sa pot folosi aceeasi functie de get_signals

X_test = []
signals_gen_test = get_signals(test_df, test_path)

for signal, label in signals_gen_test:
    sample = librosa.feature.mfcc(signal, sr=sample_rate)
    X_test.append(sample)

X_test = librosa.util.normalize(X_test, axis=1)


# In[35]:


X_test_flat = X_test.reshape(X_test.shape[0], X_test.shape[1] * X_test.shape[2])


# In[39]:


y_pred = svc_model.predict(X_test_flat)
print(len(y_pred))
print(y_pred[:100])


# In[40]:


def salvare_predictii(y_pred, nume_model):
    test_df['label'] = y_pred

    with open('predictions_' + nume_model + '.txt', 'w') as fout:
        fout.write('name,label\n')
        for index, [sample, label] in test_df.iterrows():
            fout.write(str(sample))
            fout.write(',')
            fout.write(str(label))
            fout.write('\n')


# In[41]:


salvare_predictii(y_pred, 'svc_C10_mask')


# In[78]:


from sklearn.linear_model import LogisticRegression

lr = LogisticRegression(max_iter=500)
lr.fit(X_train_flat[mask], y_train[mask])


# In[79]:


lr.score(X_val_flat, y_val)


# In[80]:


from sklearn.neural_network import MLPClassifier

mlp = MLPClassifier(max_iter=500)
mlp.fit(X_train_flat[mask], y_train[mask])


# In[81]:


mlp.score(X_val_flat, y_val)


# In[86]:


y_pred = mlp.predict(X_test_flat)
salvare_predictii(y_pred, 'mlp_mask')


# In[55]:


get_ipython().run_line_magic('pinfo', 'xgb.XGBClassifier')


# In[56]:


bst = xgb.XGBClassifier(objective='binary:logistic', verbosity=1, gamma=0.1, max_depth=4)
bst.fit(X_train_flat, y_train,)


# In[57]:


bst.score(X_val_flat, y_val)


# In[70]:


y_pred = bst.predict(X_test_flat)
salvare_predictii(y_pred, 'xgb_g01_md4')


# # Modele cu keras
# 
# cnn:
# fara masca - 66.1%,
# cu masca - 68.2%
# 
# cnn1d:
# fara masca - 67.6%,
# cu masca - 64.9%

# In[71]:


X_train_cnn = X_train.reshape(X_train.shape[0], X_train.shape[1], X_train.shape[2], 1)
y_train_categ = to_categorical(y_train, 2)


# In[100]:


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


# In[101]:


cnn.fit(X_train_cnn[mask], y_train_categ[mask], epochs=20, batch_size=128, validation_split=0.1, shuffle=True)


# In[72]:


X_val_cnn = X_val.reshape(X_val.shape[0], X_val.shape[1], X_val.shape[2], 1)
y_val_categ = to_categorical(y_val, 2)


# In[102]:


cnn.evaluate(X_val_cnn, y_val_categ)


# In[93]:


cnn.save('cnn_mask.h5')


# In[94]:


X_test_cnn = X_test.reshape(X_test.shape[0], X_test.shape[1], X_test.shape[2], 1)
y_pred_cnn = np.argmax(cnn.predict(X_test_cnn), axis=1)
salvare_predictii(y_pred_cnn, 'cnn_mask')


# In[73]:


X_train_cnn1d = X_train_flat.reshape(X_train_flat.shape[0], X_train_flat.shape[1], 1)
X_val_cnn1d = X_val_flat.reshape(X_val_flat.shape[0], X_val_flat.shape[1], 1)
X_test_cnn1d = X_test_flat.reshape(X_test_flat.shape[0], X_test_flat.shape[1], 1)


# In[74]:


X_train_cnn1d.shape


# In[75]:


cnn1d = Sequential()
cnn1d.add(Conv1D(16, 3, activation='tanh', strides=1, padding='same', input_shape=X_train_cnn1d.shape[1:]))
cnn1d.add(Conv1D(32, 3, activation='relu', strides=1, padding='same'))
cnn1d.add(Conv1D(64, 3, activation='relu', strides=1, padding='same'))
cnn1d.add(Dropout(0.2))
cnn1d.add(Conv1D(128, 3, activation='relu', strides=1, padding='same'))
cnn1d.add(MaxPool1D(2))
cnn1d.add(Dropout(0.5))
cnn1d.add(Flatten())
cnn1d.add(Dense(128, activation='relu'))
cnn1d.add(Dropout(0.5))
cnn1d.add(Dense(64, activation='relu'))
cnn1d.add(Dropout(0.2))
cnn1d.add(Dense(16, activation='relu'))
cnn1d.add(Dense(8, activation='relu'))
cnn1d.add(Dense(2, activation='softmax'))
cnn1d.summary()
cnn1d.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['acc'])


# In[77]:


cnn1d.fit(X_train_cnn1d[mask], y_train_categ[mask], epochs=20, batch_size=128, validation_split=0.1, shuffle=True)


# In[78]:


cnn1d.evaluate(X_val_cnn1d, y_val_categ)


# In[142]:


cnn1d.save('cnn1d.h5')


# In[144]:


y_pred_cnn1d = np.argmax(cnn1d.predict(X_test_cnn1d), axis=1)
salvare_predictii(y_pred_cnn1d, 'cnn1d')

