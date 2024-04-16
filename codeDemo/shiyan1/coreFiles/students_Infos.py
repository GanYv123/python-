from classFiles.Student import Student
import random
import os
from classFiles.ManageFiles import Manage_file

class students_info_count:

#Excellent, good, qualified, unqualified
#优秀 及格 学生
      # 优秀 及格 学生
    classifity_dict = {
        "exc_list": [],
        "good_list": [],
        "qua_list": [],
        "unqua_list": []
    }


    @staticmethod
    def get_stuDict():
        stu_dict = {}
        m_f = Manage_file("info.txt")
        stu_lines = m_f.read_file()  # 逐行读取文件内容
        if stu_lines:  # 检查文件内容是否为空
            for line in stu_lines:
                s = line.strip().split('\t')
                if len(s) == 3:
                    stu_name, stu_score, stu_GPA = s
                    stu_dict[stu_name] = {'score': float(stu_score), 'point': float(stu_GPA)}
            # for name, info in stu_dict.items():
            #     print(f"Name: {name}, Score: {info['score']}, GPA: {info['point']}")
        else:
            print("File is empty.")
        return stu_dict




    @staticmethod
    def classification(student) -> None:
        if float(student.getGPA()) >= 3.0:
            students_info_count.classifity_dict["exc_list"].append(student)
        elif 3.0 > float(student.getGPA()) >= 2.0:
            students_info_count.classifity_dict["good_list"].append(student)
        elif 2.0 > float(student.getGPA()) >= 1.0:
            students_info_count.classifity_dict["qua_list"].append(student)
        elif float(student.getGPA()) == 0:
            students_info_count.classifity_dict["unqua_list"].append(student)

    @staticmethod #
    def print_classification() -> None:
        order = ["exc_list", "good_list", "qua_list", "unqua_list"]
        for category in order:
            print(f"{category}:")
            for student in students_info_count.classifity_dict[category]:
                print(f"  {student.getName()} - GPA: {student.getGPA()}",end= '...\n')

    @staticmethod
    def file_is_exist(file_name):
        return os.path.exists(file_name)

    @staticmethod
    def is_empty(file_name):
        return os.path.getsize(file_name)

    @staticmethod
    def parse_students(lines) -> list[str]:
        m_students = []
        for stu in lines:
            s = stu.strip().split('\t')
            if len(s) == 3:
                stu_name, stu_score, stu_GPA = s
                m_students.append(Student(stu_name, float(stu_score)))
        return m_students

    @classmethod
    def studentInfo(cls):
        students = []
        m_f = Manage_file("info.txt")
        if cls.file_is_exist("info.txt") and cls.is_empty("info.txt") != 0: # 如果存在且不为空，读取文件内容进行初始化
            print("文件存在，读取info")
            students = cls.parse_students(m_f.read_file())

        else: # 不存在或为空，初始化
            for i in range(1, 20):
                students.append(Student("学生{}".format(i), random.randrange(40, 101)))
                
        file_info = ""
        for student in students:
            students_info_count.classification(student)
            infos = student.getName() + "\t" + str(student.getScore()) + "\t" + student.getGPA()
            #print(infos)
            file_info += (infos + '\n')

        m_f.write_file(file_info)

        #students_info_count.print_classification()
        
