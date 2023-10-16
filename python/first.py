import random

in_x = int(input('输入整数:'))
rand_x = random.randint(1, 6)
print('程序随机数：%d' % rand_x)

if in_x > rand_x:
    print('用户赢')
elif in_x < rand_x:
    print('程序赢')
else:
    print('打平')