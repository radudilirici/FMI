import numpy as np
from collections import defaultdict
import sys
import random
from tqdm import trange

import gym
import numpy as np
from collections import defaultdict
import matplotlib.pyplot as plt
import pickle
from tqdm import trange
import seaborn as sns
import pandas as pd
from random import random
import abc
import warnings
warnings.filterwarnings("ignore")

def TrainBJAgent(env, BJAgent, numEpisodes=200):
        
    for episodeIndex in trange(numEpisodes):
        
        state = env.reset()
        while True:

            # get action
            epsAtEpisode = BJAgent.get_epsilon(episodeIndex)
            action = BJAgent.select_action(state, epsilon=epsAtEpisode)

            # step environment
            next_state, reward, done, info = env.step(action)

            # update agent
            BJAgent.updateExperience(state, action, reward, next_state, episodeIndex)

            # move to next state
            state = next_state
            
            if done:
                break

class BJAgent:
    def __init__(self, env, gamma=0.8, alpha=1e-1,
                 start_epsilon=1., end_epsilon=1e-2, epsilon_decay=0.999):

        self.env = env
        self.n_action = self.env.action_space.n
        self.gamma = gamma
        self.alpha = alpha

        # action values
        self.q = defaultdict(lambda: np.zeros(self.n_action))  # action value

        # epsilon greedy parameters
        self.start_epsilon = start_epsilon
        self.end_epsilon = end_epsilon
        self.epsilon_decay = epsilon_decay

    # get epsilon
    def get_epsilon(self, n_episode):
        epsilon = max(self.start_epsilon * (self.epsilon_decay ** n_episode), self.end_epsilon)
        return (epsilon)

    # select action based on epsilon greedy
    def select_action(self, state, epsilon):
        # implicit policy; if we have action values for that state, choose the largest one, else random
        best_action = np.argmax(self.q[state]) if state in self.q else self.env.action_space.sample()
        if np.random.rand() > epsilon:
            action = best_action
        else:
            action = self.env.action_space.sample()
        return (action)


class Q_BJAgent(BJAgent):
    def __init__(self, env, gamma=1.0, alpha=1e-1,
                 start_epsilon=1.0, end_epsilon=0.05, epsilon_decay=0.99999):
        super().__init__(env, gamma, alpha, start_epsilon, end_epsilon, epsilon_decay)

    # Given (state, action, reward, next_state) pair after a transition made in the e nvironment and the episode index
    def updateExperience(self, state, action, reward, next_state, n_episode):
        next_action = self.select_action(next_state, -1)  # -1 so the algorithm NEVER chooses random on second action
        # Q(s t+1, a t+1)
        next_q = self.q[next_state][next_action]
        self.q[state][action] += self.alpha * (reward + self.gamma * next_q - self.q[state][action])