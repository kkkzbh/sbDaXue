-- 1. 创建数据库JXGL
CREATE DATABASE JXGL;

-- 使用JXGL数据库
USE JXGL;

-- 2. 创建student表并插入数据
CREATE TABLE student (
    sno CHAR(9) PRIMARY KEY,
    sname VARCHAR(20) NOT NULL,
    ssex CHAR(2),
    sage SMALLINT,
    sdept VARCHAR(20)
);

-- 插入student表数据
INSERT INTO student VALUES
('201215121', '李勇', '男', 20, 'CS'),
('201215122', '刘晨', '女', 19, 'CS'),
('201215123', '王敏', '女', 18, 'MA'),
('201215125', '张立', '男', 19, 'IS');

-- 查看插入结果
SELECT * FROM student;

-- 3. 创建course表并插入数据
CREATE TABLE course (
    cno CHAR(4) PRIMARY KEY,
    cname VARCHAR(40) NOT NULL,
    cpno CHAR(4),
    ccredit SMALLINT,
    FOREIGN KEY (cpno) REFERENCES course(cno)
);

-- 插入course表数据
-- 第一步：先插入没有依赖关系的记录（cpno为NULL的记录）
INSERT INTO course VALUES
('2', '数学', NULL, 2),
('6', '数据处理', NULL, 2);

-- 第二步：插入有依赖关系的记录
INSERT INTO course VALUES
('7', 'PASCAL语言', '6', 4);
INSERT INTO course VALUES
('5', '数据结构', '7', 4);
INSERT INTO course VALUES
('1', '数据库', '5', 4);
INSERT INTO course VALUES
('4', '操作系统', '6', 3);
INSERT INTO course VALUES
('3', '信息系统', '1', 4);

-- 查看插入结果
SELECT * FROM course;

-- 4. 创建sc表并插入数据
CREATE TABLE sc (
    sno CHAR(9),
    cno CHAR(4),
    grade SMALLINT,
    PRIMARY KEY (sno, cno),
    FOREIGN KEY (sno) REFERENCES student(sno),
    FOREIGN KEY (cno) REFERENCES course(cno)
);

-- 插入sc表数据
INSERT INTO sc VALUES
('201215121', '1', 92),
('201215121', '2', 85),
('201215121', '3', 88),
('201215122', '2', 90),
('201215122', '3', 80);

-- 查看插入结果
SELECT * FROM sc;

-- 5. 向Student表增加"入学时间"属性
ALTER TABLE student ADD COLUMN enrollment_date VARCHAR(20);

-- 查看修改后的表结构
DESCRIBE student;

-- 6. 将入学时间的数据类型改为日期型
ALTER TABLE student MODIFY COLUMN enrollment_date DATE;

-- 查看修改后的表结构
DESCRIBE student;

-- 7. 删除入学时间
ALTER TABLE student DROP COLUMN enrollment_date;

-- 查看修改后的表结构
DESCRIBE student;

-- 8. 增加课程名称唯一值约束
ALTER TABLE course ADD CONSTRAINT unique_cname UNIQUE(cname);

-- 验证唯一约束是否生效
-- 以下语句应该会失败，因为已经存在名为"数据库"的课程
-- INSERT INTO course VALUES ('8', '数据库', NULL, 3);
