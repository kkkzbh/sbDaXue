
use jxgl;

INSERT INTO student
VALUES ('201215127','刘明','男',20,'CS');

INSERT INTO SC
VALUES
    ('201215127', '1', NULL),
    ('201215127', '2', NULL),
    ('201215127', '4', NULL);

CREATE TABLE avg_grade (
    sno CHAR(9) PRIMARY KEY,
    avgg DECIMAL(5,2)
);

INSERT INTO avg_grade
SELECT sno,AVG(grade)
FROM SC
GROUP BY sno;

UPDATE course
SET ccredit = 3
WHERE cname = '数据库';

UPDATE sc
SET grade = 0
WHERE cno = (
    SELECT cno
    FROM course
    WHERE cname = '数据库'
);

DELETE
FROM sc
WHERE cno = (
    SELECT cno
    FROM course
    WHERE cname = '数据库'
);

DELETE
FROM sc
WHERE TRUE;

UPDATE sc
SET grade = NULL
WHERE cno IN (
    SELECT cno
    FROM course
    WHERE cpno IS NULL
);

-- --------------------------------------------------------------

CREATE VIEW IS1
AS
SELECT *
FROM student
WHERE sdept = 'IS';

CREATE VIEW IS2
AS
SELECT *
FROM student
WHERE sdept = 'IS'
WITH CHECK OPTION;

INSERT INTO IS1
VALUES ('201215138','李一明','男',19,'IS');

INSERT INTO IS2
VALUES ('201215139','张一兰','女',19,'IS');

-- 正常执行，因为我确实插入的 IS

INSERT INTO IS1
VALUES ('201215142','lsm','男',19,NULL);

INSERT INTO IS2
VALUES ('201215143','zll','女',19,NULL);

-- IS2 插入失败，因为没有sdept 不符合该视图的要求(WITH CHECK OPTION)

CREATE VIEW IS3
AS
SELECT sno,sname,ssex,sage
FROM student
WHERE sdept = 'IS';

CREATE VIEW IS4
AS
SELECT sno,sname,ssex,sage
FROM student
WHERE sdept = 'IS'
WITH CHECK OPTION;

INSERT INTO IS3
VALUES ('201215150','lsim','男',19,'MA');

INSERT INTO IS3
VALUES ('201215151','lsim','男',19);

INSERT INTO IS4
VALUES ('201215152','ZSL','女',19,'MA');

INSERT INTO IS4
VALUES ('201215153','Z5L','女',19);

SELECT * FROM IS1;
SELECT * FROM IS2;
SELECT * FROM student;

-- 确实IS4 实现了WITH CHECK OPTION 不允许插入
-- 同时对于四个参数的IS3 也能完成五个参数的插入

UPDATE IS1
SET sdept = 'CS'
WHERE sname = '李一明';

UPDATE IS2
SET sdept = 'CS'
WHERE sname = '张一兰';

-- 确实实现了 第二个IS2视图是不允许改的

DROP VIEW IS3,IS4;

-- -------------------------------------------------------------

DROP VIEW IS3;

CREATE VIEW IS3
AS
SELECT student.sno AS sno,sname AS sname,grade AS grade,sdept AS sdept
FROM student
JOIN sc ON student.sno = sc.sno
WHERE sc.cno = (
    SELECT cno
    FROM course
    WHERE cname = '数据库'
);

-- 有 warning 但是运行正常
CREATE VIEW IS4
AS
SELECT sno,sname,grade,sdept
FROM IS3
WHERE grade >= 90 AND
      sdept = 'IS';

SELECT * FROM IS4;

-- ----------------------------------------------------

CREATE VIEW sbrith
AS
SELECT sno,sname,(YEAR(CURRENT_DATE) - sage) AS birthday
FROM student;

CREATE VIEW smax
AS
SELECT course.cno,max(grade)
FROM course
LEFT JOIN sc ON course.cno = sc.cno
GROUP BY cno;

SELECT * FROM smax;

SELECT * FROM IS3;
DROP VIEW IS3 RESTRICT;
SELECT * FROM IS4;
-- 删掉了,应该是MySQL 他让删除

DROP VIEW IS3 CASCADE;
SELECT * FROM IS4;

-- 被级联删除了

SELECT sno,sname,sage
FROM IS1
WHERE sage < 19;

SELECT sno,sname
FROM IS3
WHERE grade = (
    SELECT MIN(grade)
    FROM IS3
);

SELECT * FROM smax;

SELECT cno,`max(grade)`
FROM smax
WHERE `max(grade)` > 90;

-- 可以执行，显然可以，用反引号引用默认名字

UPDATE IS1
SET sage = 0
WHERE TRUE;

UPDATE smax
SET `max(grade)` = 100
WHERE cno = 1;

-- 不可以，因为 `max(grade)` 是用聚类函数计算的列

DELETE
FROM IS1
WHERE sname = '张立';

-- 没法删，被外键引用了 course之类的

