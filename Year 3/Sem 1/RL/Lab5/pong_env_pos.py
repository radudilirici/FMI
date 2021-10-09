import gym
from time import time, sleep
import numpy as np
from matplotlib import pyplot as plt
import random


DISPLAY_HEIGHT = 450
DISPLAY_WIDTH = 750

BAR_LENGTH = 60
BAR_WIDTH = 10
BAR_STEP = 6

BALL_SIZE = 10
INITIAL_BALL_SPEED = 8
SPEED_CHANGE_TIME = 20  # seconds
SPEED_CHANGE = 1
MAX_SPEED = 12

BAR_OFFSET = 50
p1_x = BAR_OFFSET
p2_x = DISPLAY_WIDTH - BAR_OFFSET

p1_y, p2_y, ball_x, ball_y = 0, 0, 0, 0

UP, DOWN, RIGHT, LEFT = -1, 1, 1, -1

def ball_collides_left(ball_x, ball_y, ball_dir_x, p1_y):
    if ball_dir_x == LEFT and \
    ball_x <= p1_x + BAR_WIDTH + BALL_SPEED // 2:
        if ball_y > p1_y - BALL_SIZE and \
        ball_y < p1_y + BAR_LENGTH + BALL_SIZE - 1:
            return 1
        return -1
    return 0


def ball_collides_right(ball_x, ball_y, ball_dir_x, p2_y):
    if ball_dir_x == RIGHT and \
    p2_x - BALL_SPEED // 2 <= ball_x:
        if ball_y > p2_y - BALL_SIZE and \
        ball_y < p2_y + BAR_LENGTH + BALL_SIZE - 1:
            return 1
        return -1
    return 0


def ball_collides_up(ball_y):
    return ball_y <= BALL_SPEED // 2 and ball_dir_y < 0


def ball_collides_down(ball_y):
    return ball_y >= DISPLAY_HEIGHT - BALL_SIZE - BALL_SPEED // 2 and ball_dir_y > 0


def ball_got_out(ball_x):
    return ball_x <= BAR_OFFSET or \
        ball_x >= DISPLAY_WIDTH - BAR_OFFSET


class env:
    action_space = gym.spaces.Discrete(3)
    observation_space = None
    obs = np.zeros(4)

    metadata = {'render.modes': []}
    reward_range = (-float('inf'), float('inf'))
    spec = None
    goal_reward = 5
    hit_reward = 1
    step_reward = -0.02

    def reset(self):

        random.seed()

        global p1_y, p2_y, ball_x, ball_y, ball_dir_x, ball_dir_y, BALL_SPEED

        p1_y = p2_y = (DISPLAY_HEIGHT - BAR_LENGTH) // 2 + random.randint(-5, 5)
        ball_x = (DISPLAY_WIDTH - BALL_SIZE) // 2
        ball_y = (DISPLAY_HEIGHT - BALL_SIZE) // 2
        aux = random.randint(0, 1) * 2 - 1
        ball_dir_x = aux
        ball_dir_y = 0
        BALL_SPEED = INITIAL_BALL_SPEED

        self.obs = np.array([p2_x + BAR_WIDTH // 2, \
                             p2_y + BAR_LENGTH // 2, \
                             ball_x + BALL_SIZE // 2, \
                             ball_y + BALL_SIZE // 2])

        return self.obs

    def step(self, action):

        global p1_y, p2_y, ball_x, ball_y, ball_dir_x, ball_dir_y, BALL_SPEED

        p1_action = 0
        if p1_y > ball_y:
            p1_action = -1
        elif p1_y + BAR_LENGTH< ball_y:
            p1_action = 1

        user_input = [p1_action, action - 1]
        done = False
        reward = 0
        if action != 1:
            reward += self.step_reward

        # updating player positions
        new_p1_y = p1_y + user_input[0] * BAR_STEP
        if 0 <= new_p1_y < DISPLAY_HEIGHT - BAR_LENGTH:
            p1_y = new_p1_y

        new_p2_y = p2_y + user_input[1] * BAR_STEP
        if 0 <= new_p2_y < DISPLAY_HEIGHT - BAR_LENGTH:
            p2_y = new_p2_y

        # updating ball position
        ball_x += ball_dir_x * BALL_SPEED
        ball_y += int(ball_dir_y * BALL_SPEED)

        left_c = ball_collides_left(ball_x, ball_y, ball_dir_x, p1_y)
        if left_c == 1:
            ball_dir_x = RIGHT
            ball_dir_y = (ball_y + BALL_SIZE / 2 - (p1_y + BAR_LENGTH / 2)) / (BAR_LENGTH / 2)
            if BALL_SPEED < MAX_SPEED:
                BALL_SPEED += SPEED_CHANGE
        # elif left_c == -1:
            # done = True
            # reward += self.goal_reward

        right_c = ball_collides_right(ball_x, ball_y, ball_dir_x, p2_y)
        if right_c == 1:
            ball_dir_x = LEFT
            ball_dir_y = (ball_y + BALL_SIZE / 2 - (p2_y + BAR_LENGTH / 2)) / (BAR_LENGTH / 2)
            if BALL_SPEED < MAX_SPEED:
                BALL_SPEED += SPEED_CHANGE
            reward += self.hit_reward * (BALL_SPEED / INITIAL_BALL_SPEED)
            # done = True
        # elif right_c == -1:
        #     done = True
        #     reward -= abs(ball_y + BALL_SIZE // 2 - (p2_y + BAR_LENGTH // 2)) ** 2 / 100

        if ball_collides_up(ball_y) or ball_collides_down(ball_y):
            ball_dir_y = -ball_dir_y
            if ball_y < 0:
                ball_y = -ball_y
            elif ball_y >= DISPLAY_HEIGHT - BALL_SIZE:
                ball_y = DISPLAY_HEIGHT - BALL_SIZE - 10

        self.obs = np.array([p2_x + BAR_WIDTH // 2, \
                             p2_y + BAR_LENGTH // 2, \
                             ball_x + BALL_SIZE // 2, \
                             ball_y + BALL_SIZE // 2])

        if ball_got_out(ball_x):
            done = True
            if ball_x <= BAR_WIDTH + BAR_OFFSET:
                reward += self.goal_reward
            else:
                reward -= ((ball_y + BALL_SIZE // 2 - (p2_y + BAR_LENGTH // 2)) / DISPLAY_HEIGHT  * 2) ** 2

        return self.obs, reward, done, {}

    def render(self):
        image = np.zeros((DISPLAY_HEIGHT, DISPLAY_WIDTH, 3), dtype=np.uint8 )

        for i in range(BAR_LENGTH):
            for j in range(BAR_WIDTH):
                for k in range(3):
                    image[p1_y + i, p1_x + j, k] = 255

        for i in range(BAR_LENGTH):
            for j in range(BAR_WIDTH):
                for k in range(3):
                    image[p2_y + i, p2_x + j, k] = 255

        for i in range(BALL_SIZE):
            for j in range(BALL_SIZE):
                for k in range(3):
                    image[ball_y + i, ball_x + j, k] = 255

        return image

    def close(self):
        """Flush all monitor data to disk and close any open rending windows."""
        super(gym.wrappers.Monitor, self).close()
