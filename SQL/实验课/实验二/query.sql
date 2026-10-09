

USE JXGL2;

-- 1.
SELECT student.Sno,student.Sname,student.Sdept,sc.cno,sc.grade
FROM student
JOIN sc ON student.Sno = sc.Sno;

-- 2.
SELECT DISTINCT student.Sno,student.Sname,student.Sdept
FROM student
JOIN sc ON student.Sno = sc.Sno
WHERE grade >= 90;

-- 3.
SELECT DISTINCT student.Sno,student.Sname,student.Sdept
FROM student
JOIN sc ON student.Sno = sc.Sno
WHERE grade >= 90 and Sdept = 'CS';

-- 4.
SELECT x.cno no,y.cpno ppno
FROM course x
JOIN course y ON x.cpno = y.cno
WHERE y.cpno IS NOT NULL;

-- 5.
SELECT student.sno,sname,sdept,cno,grade
FROM sc
JOIN student ON sc.sno = student.sno;

-- 6.
SELECT student.sno,sname,sdept,cno,grade
FROM student
LEFT JOIN sc ON student.sno = sc.sno;

-- 7.
SELECT student.sno,sname,sdept,cname,grade
FROM student
JOIN sc ON student.sno = sc.sno
JOIN course ON sc.cno = course.cno;

-- 8.
SELECT student.sno,sname
FROM sc
JOIN student ON sc.sno = student.sno
WHERE sc.cno = 1;

-- 9.
SELECT student.sno,sname
FROM student
JOIN sc ON student.sno = sc.sno
JOIN course ON sc.cno = course.cno
WHERE cname = '数据库' AND ssex = '男';

-- 10.
SELECT sno,sname
FROM student
WHERE EXISTS (
    SELECT *
    FROM sc
    WHERE student.sno = sc.sno AND
          EXISTS (
              SELECT *
              FROM course
              WHERE sc.cno = course.cno AND
                    course.cname = '数据库'
          )
);

-- 11.
SELECT sno,sname,sage,sdept
FROM student
WHERE sage > ANY (
    SELECT sage
    FROM student
    WHERE sname = '李勇'
);

-- 12.
SELECT sno,sname,sage,sdept
FROM student
WHERE sage > (
    SELECT AVG(sage)
    FROM student
    WHERE sdept = 'CS'
);

-- 13.
SELECT sno,sname,sage,sdept
FROM student
WHERE sage > (
    SELECT MAX(sage)
    FROM student
    WHERE sdept = 'CS'
);

-- 14.
SELECT sno,sname,sage,sdept
FROM student
WHERE sdept != 'CS' AND
      sage > (
          SELECT MAX(sage)
          FROM student
          WHERE sdept = 'CS'
      );

-- 15.
SELECT sno,cno
FROM sc x
WHERE grade > (
    SELECT AVG(grade)
    FROM sc y
    WHERE x.sno = y.sno
);

-- 16.
SELECT sno,cno
FROM sc x
WHERE grade > (
    SELECT AVG(grade)
    FROM sc y
    WHERE x.cno = y.cno
);

-- 17.
SELECT sno,sname,sdept,sage
FROM student x
WHERE sage > (
    SELECT AVG(sage)
    FROM student y
    WHERE x.sdept = y.sdept
);

-- 18.
SELECT sname
FROM student
JOIN sc ON student.sno = sc.sno
JOIN course ON sc.cno = course.cno
WHERE cname = '数学';

-- 19.
SELECT sname
FROM student
WHERE sname NOT IN (
    SELECT sname
    FROM student
    JOIN sc ON student.sno = sc.sno
    JOIN course ON sc.cno = course.cno
    WHERE cname = '数学'
);

-- 20.
SELECT COUNT(*) cnt,AVG(grade) avgg
FROM sc
GROUP BY cno;

-- 21.
SELECT sno,AVG(grade)
FROM sc
GROUP BY sno
HAVING COUNT(*) >= 2 AND
       MIN(grade) >= 60;

-- 22.
SELECT sno,AVG(grade)
FROM sc
WHERE sno LIKE '2012%'
GROUP BY sno
HAVING COUNT(*) >= 2 AND
       MIN(grade) >= 60
ORDER BY AVG(grade);

-- 23.
SELECT sno,AVG(grade),COUNT(*)
FROM sc
WHERE grade >= 60
GROUP BY sno
ORDER BY AVG(grade) DESC,COUNT(*) DESC;

-- 24.
SELECT sno,AVG(grade),COUNT(*)
FROM sc
GROUP BY sno
HAVING MIN(grade) >= 60
ORDER BY AVG(grade) DESC,COUNT(*) DESC;

-- 25.
SELECT sno,sname,sdept
FROM student
WHERE sdept != 'CS' AND
      sage < ALL (
          SELECT sage
          FROM student
          WHERE sdept = 'CS'
      );

-- 26.
SELECT sno,grade
FROM sc
WHERE cno = 1 AND
      grade > (
        SELECT AVG(grade)
        FROM sc
        WHERE cno = 1
      );

-- 27.
SELECT sno,sname,sdept
FROM student x
WHERE sage > (
    SELECT AVG(sage)
    FROM student y
    WHERE x.sdept = y.sdept
);

-- 28.
SELECT sno,sname
FROM student
WHERE NOT EXISTS (
    SELECT cno
    FROM course
    WHERE NOT EXISTS (
        SELECT cno
        FROM sc
        WHERE sc.sno = student.sno AND
              sc.cno = course.cno
    )
);

-- 29.
SELECT sno,sname
FROM student
WHERE NOT EXISTS (
    SELECT cno
    FROM sc x
    WHERE x.sno = '201215122' AND
        NOT EXISTS (
        SELECT cno
        FROM sc y
        WHERE y.sno = student.sno AND
            y.cno = x.cno
    )
);

-- 30.
SELECT student.sno,sname
FROM student
JOIN SC ON student.Sno = SC.Sno
WHERE cno = 1
UNION
SELECT student.sno,sname
FROM student
JOIN SC ON student.Sno = SC.Sno
WHERE cno = 2;

SELECT student.sno,sname
FROM student
JOIN SC ON student.Sno = SC.Sno
WHERE cno = 1
INTERSECT
SELECT student.sno,sname
FROM student
JOIN SC ON student.Sno = SC.Sno
WHERE cno = 2;

SELECT student.sno,sname
FROM student
JOIN SC ON student.Sno = SC.Sno
WHERE cno = 1
EXCEPT
SELECT student.sno,sname
FROM student
JOIN SC ON student.Sno = SC.Sno
WHERE cno = 2;

