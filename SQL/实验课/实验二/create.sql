-- 1.创建数据库"JXGL2"
CREATE DATABASE JXGL2;

USE jxgl2;
-- 2.在数据库"JXGL2"中建立表"student"，并插入，记录如下：
CREATE TABLE student (
    Sno CHAR(9) PRIMARY KEY,
    Sname CHAR(20) UNIQUE,
    Ssex CHAR(2),
    Sage SMALLINT,
    Sdept CHAR(20)
);

INSERT INTO student VALUES
    ('201215121', '李勇', '男', 20, 'CS'),
    ('201215122', '刘晨', '女', 19, 'CS'),
    ('201215123', '王敏', '女', 18, 'MA'),
    ('201215124', '张立', '女', 20, 'MA'),
    ('201215125', '吴峰', '男', 19, 'IS'),
    ('201215126', '张向东', '男', 24, 'CS');

-- 3.在数据库"JXGL2"中建立表"course"，并插入，记录如下：
CREATE TABLE course (
    Cno CHAR(4) PRIMARY KEY,
    Cname CHAR(20) NOT NULL,
    Cpno CHAR(4),
    Ccredit SMALLINT,
    FOREIGN KEY (Cpno) REFERENCES course (Cno)
);

INSERT INTO course(Cno, Cname, Cpno, Ccredit) VALUES
    ('2', '数学', NULL, 2),
    ('6', '数据处理', NULL, 2),
    ('4', '操作系统', '6', 3),
    ('7', 'PASCAL语言', '6', 4),
    ('5', '数据结构', '7', 4),
    ('1', '数据库', '5', 4),
    ('3', 'Design_Pattern', '1', 4);

-- 4.在数据库"JXGL2"中建立表"sc"，并插入，记录如下：
CREATE TABLE SC (
    Sno CHAR(9),
    Cno CHAR(4),
    grade SMALLINT,
    PRIMARY KEY(Sno, Cno),
    FOREIGN KEY(Sno) REFERENCES student (Sno),
    FOREIGN KEY(Cno) REFERENCES course (Cno)
);

INSERT INTO SC VALUES
    ('201215121', '1', 92),
    ('201215121', '2', 85),
    ('201215121', '3', 100),
    ('201215121', '4', 88),
    ('201215121', '5', 0),
    ('201215121', '6', 97),
    ('201215121', '7', 8),
    ('201215122', '2', 90),
    ('201215122', '3', 80),
    ('201215123', '5', 59),
    ('201215124', '1', 89),
    ('201215125', '1', 95),
    ('201215125', '2', 0),
    ('201215125', '3', 77),
    ('201215125', '4', 97);
