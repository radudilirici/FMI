# Lab 5: Q Learning for continuous and multivariate state on https://gym.openai.com/envs/MountainCar-v0/
# How would you solve such a problem when the state is a continuous and multivariate value ?

# Try to solve this on your own
# Try using grid search parameters method to discover the best ones

import numpy as np
import gym
from gym import wrappers
import time

# Imports specifically so we can render outputs in Jupyter.
import matplotlib.pyplot as plt
#%matplotlib inline
from JSAnimation.IPython_display import display_animation
from matplotlib import animation
from IPython.display import display
from collections import deque

### Hyperparams

# In how many slices discretize the continuous space, the bigger, the smoother. but it increases a lot the time to converge !
# Try and check to see how they work !
numStates_pos = 10
numStates_speed = 20
numStates = np.array([numStates_pos, numStates_speed])

# The environment low, high and interval mapped per state
env_low = None
env_high = None
env_dx = None

# Number of episodes
numEpisodes = 100
maxStepsPerEpisode = 200 #Number of max actions taken per episode. If in 200 steps it's not done, the environment takes it as fail.

# Tweaking params
initial_lr = 1.0 # Initial Learning Rate
min_lr = 0.001 # Minimum Learning Rate
lr_decay = 0.9996
gamma = 1.0 # Discount factor
epsilon_start = 1.0 # Allow the model to do a lot of trial and error on the beggining
epsilon_decay = 0.999 # Decay per episode.
epsilon_end = 0.01 # The end point / min of the epsilon

# get epsilon by Episode
def get_epsilon(n_episode):
    epsilon = max(epsilon_start * (epsilon_decay ** n_episode), epsilon_end)
    return (epsilon)


def obs_to_state(obs):
    """ Maps an observation to state """

    position = int((obs[0] - env_low[0])/env_dx[0])
    speed = int((obs[1] - env_low[1])/env_dx[1])
    return position, speed


def run_episode(env, policy=None, render=False):
    obs = env.reset()
    total_reward = 0
    step_idx = 0
    frames = []
    for _ in range(maxStepsPerEpisode):
        if render:
            frames.append(env.render(mode='rgb_array'))
        if policy is None:
            action = env.action_space.sample()
        else:
            pos, speed = obs_to_state(obs)
            action = policy[pos][speed]
        obs, reward, done, _ = env.step(action)
        total_reward += gamma ** step_idx * reward
        step_idx += 1
        if done:
            break

    if render:
        env.render()
        env.close()
    return total_reward


# select action based on epsilon greedy
def select_action(env, q_table, state, epsilon):
    position, speed = state
    # implicit policy; if we have action values for that state, choose the largest one, else random
    if np.random.rand() > epsilon:
#         logits = q_table[position][speed]
#         logits_exp = np.exp(logits)
#         probs = logits_exp / np.sum(logits_exp)
#         action = np.random.choice(env.action_space.n, p=probs)  # asa era la prof
        action = np.argmax(q_table[position][speed])
    else:
        action = env.action_space.sample()
    return action

# Given (state, action, reward, next_state) pair after a transition made in the e nvironment and the episode index
def updateExperience(env, q_table, state, action, reward, next_state, lr):
#     next_action = select_action(env, q_table, next_state, -1)  # -1 so the algorithm NEVER chooses random on second action
    # Q(s t+1, a t+1)
    position, speed = state
    next_position, next_speed = next_state
    next_q = np.max(q_table[next_position][next_speed])
    q_table[position][speed][action] += lr * (reward + gamma * next_q - q_table[position][speed][action])

def train_q_learning(env):
    print('Start Q-Learning training:')
    display_freq = min(numEpisodes // 10, 1000)

    # Initialize Q-Table
    q_table = np.random.uniform(-1, 1, (numStates[0], numStates[1], 3))  # [number_of_positions x number_of_speeds x number_of_actionst]
    last100_moving_total = 0
    last100_rewards = deque()
    SOLVED = False
    last_total_rewards = [] # For stat purposes, accumultates some episode rewards
    
    for episode in range(numEpisodes):
        eps = get_epsilon(episode)
        lr = max(min_lr, initial_lr * (lr_decay ** episode))
        
        obs = env.reset()
        total_reward = 0
        
        for step in range(maxStepsPerEpisode):
            state = obs_to_state(obs)
            action = select_action(env, q_table, state, eps)
            
            # step environment
            obs, reward, done, info = env.step(action)
            next_state = obs_to_state(obs)
            total_reward += reward
            
            updateExperience(env, q_table, state, action, reward, next_state, lr)
            
            if done:
                break
                
        last100_rewards.append(total_reward)
        last100_moving_total += total_reward
        
        while len(last100_rewards) > 100:
            removedItem = last100_rewards.popleft()
            last100_moving_total -= removedItem
            
        last100_moving_avg = last100_moving_total / len(last100_rewards)
        if len(last100_rewards) >= 100 and last100_moving_total >= -120:
            print(f"We solved the game at episode {episode} !")
            SOLVED = True
            break


        if episode % display_freq == 0:  # Write out partial results
            print(f'At episode: {episode+1} - Reward mean from last 100 episodes: {last100_moving_avg}. - LR:{lr:0.4f} - eps:{eps:0.4f}')
            last_total_rewards.clear()
        
    print('Training finished!')
    solution_policy = np.argmax(q_table, axis=2)
    solution_policy_scores = [run_episode(env, solution_policy, False) for _ in range(1000)]
    print("Average score of solution on a dry run= ", np.mean(solution_policy_scores))

    return solution_policy


if __name__ == '__main__':
    env_name = 'MountainCar-v0'
    env = gym.make(env_name)

    # Read the env things
    env_low = env.observation_space.low
    env_high = env.observation_space.high
    env_dx = (env_high - env_low) / numStates

    # Train a policy. TODO: save it
    sol_policy = train_q_learning(env)


    # Play  simulation with the learned policy
    run_episode(env, sol_policy, True)