-- 1．建立数据库"JXGL"
CREATE DATABASE JXGL;

-- 使用JXGL数据库
USE JXGL;

-- 2.在数据库"JXGL"中建立表student，定义主码，并录入数据
CREATE TABLE student (
    Sno CHAR(9) PRIMARY KEY,
    Sname CHAR(20) UNIQUE,
    Ssex CHAR(2),
    Sage SMALLINT,
    Sdept CHAR(20)
);

INSERT INTO student
VALUES
    ('201215121','李勇','男',20,'CS'),
    ('201215122','刘晨','女',19,'CS'),
    ('201215123','王敏','女',18,'MA'),
    ('201215124','李莉','女',20,'MA'),
    ('201215125','张立','男',19,'IS'),
    ('201215126','刘晓意','男',24,'CS');

-- 3.在数据库"JXGL"中建立表course，定义主码和外码，并录入数据
CREATE TABLE course (
    Cno CHAR(4) PRIMARY KEY,
    Cname CHAR(20) NOT NULL,
    Cpno CHAR(4),
    Ccredit SMALLINT,
    FOREIGN KEY (Cpno) REFERENCES course (Cno)
);

INSERT INTO course(Cno, Cname, Cpno, Ccredit)
VALUES
    ('2','数学',NULL,2),
    ('6','数据处理',NULL,2),
    ('4','操作系统','6',3),
    ('7','PASCAL语言','6',4),
    ('5','数据结构','7',4),
    ('1','数据库','5',4),
    ('3','Design   Pattern','1',4);

-- 4.在数据库"JXGL"中建立表sc，定义主码和外码，并录入数据
CREATE TABLE SC (
    Sno CHAR(9),
    Cno CHAR(4),
    grade SMALLINT,
    PRIMARY KEY(Sno, Cno),
    FOREIGN KEY(Sno) REFERENCES student (Sno),
    FOREIGN KEY(Cno) REFERENCES course (Cno)
);

INSERT INTO SC VALUES
    ('201215121','1',92),
    ('201215121','2',85),
    ('201215121','3',100),
    ('201215121','4',88),
    ('201215121','5',NULL),
    ('201215121','6',97),
    ('201215121','7',8),
    ('201215122','2',90),
    ('201215122','3',80),
    ('201215123','5',59),
    ('201215125','1',95),
    ('201215125','2',NULL),
    ('201215125','3',77),
    ('201215125','4',97);

-- 现在开始执行查询任务:

-- 1.查询全体学生的详细记录
SELECT * FROM student;

-- 2.查询全体学生的学号和姓名
SELECT Sno, Sname FROM student;

-- 3.查询全体学生的学号和姓名，使用列别名改变查询结果的列标题
SELECT Sno AS "学生编号", Sname AS "学生姓名" FROM student;

-- 4.查询选修了课程的学生学号（不去重）
SELECT Sno FROM SC;

-- 4.查询选修了课程的学生学号（去重）
SELECT DISTINCT Sno FROM SC;

-- 5.查询'CS'系全体学生的名单
SELECT * FROM student WHERE Sdept = 'CS';

-- 6.查询'1'号课的选课情况
SELECT * FROM SC WHERE Cno = '1';

-- 7.查询男同学的学号和姓名
SELECT Sno, Sname FROM student WHERE Ssex = '男';

-- 8.查询考试成绩有不及格的课程的课程号
SELECT DISTINCT Cno FROM SC WHERE grade < 60;

-- 9.查询成绩在95~99分（包括95分和99分）之间的选课记录的学号、课程号和成绩
SELECT Sno, Cno, grade FROM SC WHERE grade BETWEEN 95 AND 99;

-- 10.查询成绩不在95~99分之间的学号、课程号和成绩
SELECT Sno, Cno, grade FROM SC WHERE grade NOT BETWEEN 95 AND 99;

-- 11.查询年龄是18岁、20岁或24岁的学生的姓名和性别（方法1：使用OR）
SELECT Sname, Ssex FROM student WHERE Sage = 18 OR Sage = 20 OR Sage = 24;

-- 11.查询年龄是18岁、20岁或24岁的学生的姓名和性别（方法2：使用IN）
SELECT Sname, Ssex FROM student WHERE Sage IN (18, 20, 24);

-- 12.查询年龄既不是18岁、20岁，也不是24岁的学生的姓名和性别
SELECT Sname, Ssex FROM student WHERE Sage NOT IN (18, 20, 24);

-- 13.查询课程名中第2个字为"据"字的课程的课程号、课程名和学分
SELECT Cno, Cname, Ccredit FROM course WHERE Cname LIKE '_据%';

-- 14.查询"Design _ Pattern"课程的课程号和学分
SELECT Cno, Ccredit FROM course WHERE Cname LIKE 'Design _ Pattern';

-- 15.查询没有先行课的课程号和课程名
SELECT Cno, Cname FROM course WHERE Cpno IS NULL;

-- 16.查询男同学的学号、姓名、年龄和所在系，将查询结果按所在系的系号降序排列，同一系中的学生按年龄升序排列
SELECT Sno, Sname, Sage, Sdept FROM student 
WHERE Ssex = '男' 
ORDER BY Sdept DESC, Sage ASC;

-- 17.查询开设的课程总门数
SELECT COUNT(*) AS "课程总门数" FROM course;

-- 18.查询有学生选的课程的门数
SELECT COUNT(DISTINCT Cno) AS "有学生选的课程门数" FROM SC;

-- 19.查询全体同学的最小年龄
SELECT MIN(Sage) AS "最小年龄" FROM student;

-- 20.查询男同学的最小年龄
SELECT MIN(Sage) AS "男生最小年龄" FROM student WHERE Ssex = '男';

-- 21.查询'CS'系男同学的最小年龄
SELECT MIN(Sage) AS "CS系男生最小年龄" FROM student WHERE Ssex = '男' AND Sdept = 'CS';

-- 22.查询'201215121'同学的选课平均成绩
SELECT AVG(grade) AS "平均成绩" FROM SC WHERE Sno = '201215121';

-- 23.查询'201215121'同学的选课最高成绩
SELECT MAX(grade) AS "最高成绩" FROM SC WHERE Sno = '201215121';

-- 24.查询有选课记录的同学的学号和他相应的选课门数
SELECT Sno, COUNT(*) AS "选课门数" FROM SC GROUP BY Sno;

-- 25.查询'CS'系或'MA'系姓刘的学生的信息
SELECT * FROM student 
WHERE (Sdept = 'CS' OR Sdept = 'MA') AND Sname LIKE '刘%';

-- 26.查询缺少了成绩的学生的学号和课程号
SELECT Sno, Cno FROM SC WHERE grade IS NULL;
