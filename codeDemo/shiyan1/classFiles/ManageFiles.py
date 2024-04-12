class Manage_file:
    def __init__(self, filename):
        self.filename = filename

    def read_file(self) -> list[str]:
        try:
            with open(self.filename, 'r') as file:
                content = file.readlines()
            return content
        except FileNotFoundError:
            print(f"文件 '{self.filename}' 不存在。")
            return None
        
    def write_file(self, content):
        try:
            with open(self.filename, 'w') as file:
                file.write(content+'\n')

        except Exception as e:
            print(f"写入文件 '{self.filename}' 时出错：{e}")
    
    def read_allFile(self) -> str:
        try:
            with open(self.filename, 'r') as file:
                content = file.read()
            return content
        except FileNotFoundError:
            print(f"文件 '{self.filename}' 不存在。")
            return None
