import serial #导入模块
import serial.tools.list_ports

class Usart():
    def __init__(self):
        super(Usart,self).__init__()

    def Usart_init(self,com,bit):
        bps=int(bit)
        try:
        # 打开串口，并得到串口对象
          self.ser = serial.Serial(com, bps, timeout=0.5)
          if(self.ser.is_open):
               ret=True
               print(com,"—— 已连接")
        except Exception as e:
            print("---异常---：", e)
    
    def find(self):
        port_list = list(serial.tools.list_ports.comports())
        print(port_list)
        self.list_com=[]
        if len(port_list) == 0:
            print('无可用串口')
        else:
            for i in range(0,len(port_list)):
                com=port_list[i]
                print(com)
                com=str(com)
                n=com.find(" ")
                print(n)
                com=com[:5]
                print(com )
                self.list_com.append(com)
        return self.list_com    
    
    def Close(self):
        self.ser.close()

    def Usart_Send(self,dat):
        self.ser.write(dat)
###
#if __name__ == "__main__":
    #com=Usart()
    #com.find()
###

    