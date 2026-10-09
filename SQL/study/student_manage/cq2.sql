use homework;
-- 创建 course2 表
CREATE TABLE course2 (
    Cno CHAR(4) PRIMARY KEY,  -- 课程号，作为主键
    Cname CHAR(40),           -- 课程名
    Cpno CHAR(4),             -- 先行课号
    Ccredit SMALLINT          -- 学分
);

-- 插入数据
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('1', '数据库', '5', 4);
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('2', '数学', NULL, 2);
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('3', '信息系统', '1', 4);
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('4', '操作系统', '6', 3);
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('5', '数据结构', '7', 4);
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('6', '数据处理', NULL, 5);
INSERT INTO course2 (Cno, Cname, Cpno, Ccredit) VALUES ('7', 'PASCAL语言', '6', 4);

UPDATE course2
SET ccredit = '2'
WHERE cno = '6';

ALTER TABLE course2 ADD CONSTRAINT FK_course2_Cpno FOREIGN KEY (Cpno) REFERENCES course2(Cno);


-- 查询全部课程最低，最高，平均学分
SELECT MIN(Ccredit),MAX(Ccredit),AVG(Ccredit)
FROM course2;

-- 没有先行课的课程的最低学分
SELECT MIN(Ccredit)
FROM course2
WHERE Cpno IS NULL;

-- 3.
SELECT MAX(Ccredit)
FROM course2
WHERE Cpno IS NOT NULL;

-- 4.
SELECT COUNT(Cno),COUNT(DISTINCT Ccredit)
FROM course2;

-- 5.
SELECT SUM(ccredit)
FROM course2
WHERE cpno = '6';

-- 创建 sc2 表 (学生选课成绩表SC)
CREATE TABLE sc2 (
    Sno CHAR(8),             -- 学号
    Cno CHAR(5),             -- 课程号
    Grade INT,               -- 成绩
    Semester CHAR(5),        -- 选课学期
    Teachingclass CHAR(8),   -- 教学班
    PRIMARY KEY (Sno, Cno)   -- 学号和课程号作为联合主键
);

-- 插入数据到sc2表
INSERT INTO sc2 VALUES ('20180001', '81001', 85, '20192', '81001-01');
INSERT INTO sc2 VALUES ('20180002', '81001', 80, '20192', '81001-02');
INSERT INTO sc2 VALUES ('20180003', '81001', 81, '20192', '81001-01');
INSERT INTO sc2 VALUES ('20180004', '81001', 56, '20192', '81001-02');
INSERT INTO sc2 VALUES ('20180001', '81002', 96, '20201', '81002-01');
INSERT INTO sc2 VALUES ('20180002', '81002', 98, '20201', '81002-01');
INSERT INTO sc2 VALUES ('20180003', '81002', 76, '20201', '81002-02');
INSERT INTO sc2 VALUES ('20180002', '81003', 71, '20202', '81003-02');
INSERT INTO sc2 VALUES ('20180004', '81003', 97, '20201', '81002-02');
INSERT INTO sc2 VALUES ('20180005', '81003', 68, '20202', '81003-01');


-- 1.
SELECT sno
FROM sc2
WHERE semester = '20192'
GROUP BY sno
HAVING COUNT(cno) >= 1;

--

-- 创建 student2 表
CREATE TABLE student2 (
    Sno CHAR(8) PRIMARY KEY,  -- 学号
    Sname CHAR(20),           -- 姓名
    Ssex CHAR(2),             -- 性别
    Sage INT,                 -- 年龄
    Sdept CHAR(10)            -- 所在系
);

ALTER TABLE student2
CHANGE COLUMN Sno Sno CHAR(12);

-- 插入数据到 student2 表
INSERT INTO student2 (Sno, Sname, Ssex, Sage, Sdept) VALUES ('201215121', '李勇', '男', 20, 'CS');
INSERT INTO student2 (Sno, Sname, Ssex, Sage, Sdept) VALUES ('201215122', '刘晨', '女', 19, 'CS');
INSERT INTO student2 (Sno, Sname, Ssex, Sage, Sdept) VALUES ('201215123', '王敏', '女', 18, 'MA');
INSERT INTO student2 (Sno, Sname, Ssex, Sage, Sdept) VALUES ('201215125', '张立', '男', 19, 'IS');

-- 每个专业的人自由结组
SELECT x.sname,y.sname
FROM student2 x,student2 y
WHERE x.sdept = y.sdept AND
      x.sno < y.sno;
