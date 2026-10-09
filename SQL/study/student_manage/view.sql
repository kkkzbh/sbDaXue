use homework;

CREATE VIEW is_a1
AS
SELECT no,name,grade
FROM student
JOIN sc ON student.no = sc.sno
WHERE sc.cno = 81001 AND
      grade >= 90;

CREATE VIEW student_age(no,name,age)
AS
SELECT no,name,(EXTRACT(year FROM CURRENT_DATE) - EXTRACT(year from birth))
FROM student;

CREATE VIEW student_avg_grade(no,avg)
AS
SELECT sno,AVG(grade)
FROM sc
GROUP BY sno;

CREATE VIEW female_student
AS
SELECT *
FROM student
WHERE sex = '女';

DROP VIEW student_age;
DROP VIEW is_a1;

CREATE VIEW cc
AS
SELECT no,name,credit
FROM course;

ALTER VIEW cc
AS
SELECT *
FROM course
WHERE pno IS NULL;

SELECT no,name
FROM cc
WHERE credit = 4;

SELECT MAX(credit)
FROM cc;

UPDATE cc
SET credit = 2
WHERE name = '大数据技术概论';

SELECT *
FROM cc;