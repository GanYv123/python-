#dempo1.py 
from coreFiles.students_Infos import students_info_count
from coreFiles.server_for_qtClient import TCPServer
import threading
def main():
    # 创建并启动服务器
    server = TCPServer()
    server_thread = threading.Thread(target=server.start)
    server_thread.start()

    # 继续执行其他代码
    students_thread = threading.Thread(target=students_info_count.studentInfo)
    students_thread.start()
    
    
   
if __name__ != "__main__":
    pass
else:
    main()