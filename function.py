def pyprint(arg):
    print(" ")
    print("wellcome to jizhou's function")
    print(arg)
    return

def pydraw(arg1, arg2, arg3, arg4):
    import numpy as np
    import matplotlib.pyplot as plt
    print(arg1)
    print(" ")
    print(arg2)
    print(" ")
    print(arg3)
    print(" ")
    print(arg4)
    print(" ")
    plt.rcParams['font.sans-serif'] = ['SimHei'] # 设置字体，显示中文
    plt.rcParams['axes.unicode_minus'] = False # 坐标轴的负号正常显示
    plt.xlabel('x轴')
    plt.ylabel('y轴')
    x = np.arange(min(arg1), max(arg1), 0.1)
    y = x * arg3 + arg4
    plt.plot(arg1, arg2,'bo')
    plt.plot(x,y,'r')
    plt.show()
    return
