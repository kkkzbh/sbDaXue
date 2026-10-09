
use homework;

-- 1.
SELECT DISTINCT credit
FROM course;

-- 2.
SELECT no,name
FROM course
WHERE pno IS NULL;

-- 3.
SELECT no,name
FROM course
WHERE pno IS NOT NULL;

-- 4.
SELECT *
FROM course
WHERE credit < 4;

-- 5.
SELECT no,name
FROM course
WHERE pno = 6;

-- 6.
SELECT no,name,credit
FROM course
WHERE name LIKE '数%';

-- 7.
SELECT no,name,credit
FROM course
WHERE name LIKE '___理';

-- 8.
SELECT no,name,credit
FROM course
WHERE credit BETWEEN 2 AND 4;

-- 9.
SELECT no,name
FROM course
WHERE credit BETWEEN 1 AND 5;

SELECT no,name
FROM course
WHERE credit IN (1,2,3,4,5);

-- 10.
SELECT no,name
FROM course
WHERE pno IS NULL and credit = 3;

--
SELECT student.*,sc.*
FROM student,sc
WHERE student.no = sc.sno;

SELECT student.name,sc.sno
FROM sc
JOIN student ON sc.sno = student.no
WHERE cno = 81002 AND grade >= 90;

SELECT student.name,sc.sno
FROM student,sc
WHERE cno = 81002 AND grade >= 90 AND student.no = sc.sno;

SELECT sno,grade
FROM sc,course
WHERE sc.cno = course.no AND
      name LIKE '数据库%';

SELECT x.no,y.pno
FROM course x,course y
WHERE x.pno = y.no AND
      y.pno IS NOT NULL;

SELECT student.no,student.name,course.name,sc.grade
FROM student,course,sc
WHERE student.no = sc.sno AND
      sc.cno = course.no;

-- 查询与刘晨在同一个专业的学生学号，姓名和专业
SELECT no,name,major
FROM student
WHERE major = (
    SELECT major
    FROM student
    WHERE name = '刘晨'
);

SELECT x.no,x.name,x.major
FROM student x,student y
WHERE x.major = y.major AND
      y.name = '刘晨';

SELECT no,name
FROM student
WHERE no IN (
    SELECT sno
    FROM sc
    WHERE cno = (
        SELECT cno
        FROM course
        WHERE name = '信息系统概论'
    )
);

SELECT no,name
FROM course
WHERE no IN (
    SELECT cno
    FROM sc
    WHERE sno IN (
        SELECT no
        FROM student
        WHERE name = '李明'
    )
);

SELECT sno,cno
FROM sc x
WHERE grade >= (
    SELECT AVG(grade)
    FROM sc y
    WHERE x.sno = y.sno
);

SELECT no,name,age
FROM student
WHERE age >= (
    SELECT AVG(age)
    FROM student
);

SELECT no,name,age
FROM student x
WHERE age >= (
    SELECT AVG(age)
    FROM student y
    WHERE x.major = y.major
);

SELECT name,birth,major
FROM student x
WHERE major != '计算机科学与技术' AND
    birth > ANY (
        SELECT birth
        FROM student
        WHERE major = '计算机科学与技术'
    );

SELECT name,birth,major
FROM student x
WHERE major != '计算机科学与技术' AND
    age < ANY (
        SELECT age
        FROM student
        WHERE major = '计算机科学与技术'
    );

-- EXISTS

SELECT name
FROM student
WHERE EXISTS (
    SELECT *
    FROM SC
    WHERE no = sno AND
          cno = 81001
);

SELECT name
FROM student
WHERE NOT EXISTS (
    SELECT *
    FROM SC
    WHERE no = sno AND
          cno = 81001
);

SELECT name
FROM student
WHERE no IN (
    SELECT sno
    FROM sc
    WHERE cno = 81001
);

SELECT name
FROM student
WHERE no IN (
    SELECT sno
    FROM sc
    WHERE cno = 81001
);

SELECT no
FROM course;

SELECT name
FROM student
WHERE NOT EXISTS (
    SELECT no
    FROM course
    WHERE NOT EXISTS (
        SELECT cno
        FROM sc
        WHERE student.no = sno AND
              course.no = cno
    )
);

SELECT no
FROM student
WHERE NOT EXISTS (
    SELECT cno
    FROM sc x
    WHERE sno = '201810002' AND
          NOT EXISTS (
              SELECT cno
              FROM sc y
              WHERE student.no = y.sno AND
                    x.cno = y.cno
          )
);

SELECT *
FROM course
WHERE NOT EXISTS (
    SELECT no
    FROM student
    WHERE NOT EXISTS (
        SELECT sno
        FROM sc
        where course.no = cno AND
              student.no = sno
    )
);

SELECT course.*
FROM course,sc
WHERE course.no = cno
GROUP BY course.no,course.name,course.credit,course.pno
HAVING COUNT(*) = (SELECT COUNT(*) FROM student);

SELECT *
FROM course
WHERE no IN (
    SELECT course.no
    FROM course,sc
    WHERE course.no = cno
    GROUP BY cno
    HAVING(COUNT(*)) = (SELECT COUNT(*) FROM student)
);

SELECT name
FROM student
WHERE NOT EXISTS (
    SELECT no
    FROM course
    WHERE pno = 81002 AND
          NOT EXISTS (
              SELECT cno
              FROM sc
              WHERE student.no = sno AND
                    course.no = cno
          )
);

SELECT name
FROM student
WHERE no IN (
      SELECT student.no
      FROM student,sc,course
      WHERE student.no = sno AND
            cno = course.no AND
            pno = 81002
      GROUP BY student.no
      HAVING (COUNT(*)) = (
        SELECT COUNT(*)
        FROM course
        WHERE pno = 81002
      )
);


