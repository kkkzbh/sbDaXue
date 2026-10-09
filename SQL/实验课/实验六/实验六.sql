-- 一、实验步骤：
-- （一） 在教学管理JXGL数据库中进行如下操作：

-- 使用JXGL数据库
USE JXGL;

-- 1、建立选课表SC2，表SC2上不用定义外码约束
CREATE TABLE SC2 (
    Sno CHAR(9),
    Cno CHAR(4),
    grade SMALLINT,
    PRIMARY KEY(Sno, Cno)
);

-- 2、往SC2中输入和SC表一样的数据
INSERT INTO SC2
SELECT * FROM SC;

-- 3、定义触发器update_sc，其功能是当学生表S中的学号发生变化时，自动更新选课表SC2中该学生选课记录中的学号
DELIMITER //
CREATE TRIGGER update_sc2 
AFTER UPDATE ON student 
FOR EACH ROW
BEGIN 
    IF OLD.Sno <> NEW.Sno THEN
        UPDATE SC2 
        SET Sno = NEW.Sno 
        WHERE SC2.Sno = OLD.Sno;
    END IF;
END //
DELIMITER ;

-- 4、更新学生表student中201215121学生的学号为201215166
-- 临时禁用外键约束检查
SET FOREIGN_KEY_CHECKS = 0;

UPDATE student
SET Sno = '201215166'
WHERE Sno = '201215121';

SELECT * FROM SC2;

-- 重新启用外键约束检查
SET FOREIGN_KEY_CHECKS = 1;

-- 查看SC2中的记录变化
SELECT * FROM SC2 WHERE Sno = '201215166';

-- 5、定义触发器uc，其功能是当学生表C中的课程号发生变化时，自动更新选课表SC2中的课程号
DELIMITER //
CREATE TRIGGER uc
AFTER UPDATE ON course
FOR EACH ROW
BEGIN
    IF OLD.Cno <> NEW.Cno THEN
        UPDATE SC2
        SET Cno = NEW.Cno
        WHERE SC2.Cno = OLD.Cno;
    END IF;
END //
DELIMITER ;

-- 6、参照3步骤，试着写一下定义级联删除功能的触发器

DELIMITER //
CREATE TRIGGER delete_student_cascade
AFTER DELETE ON student
FOR EACH ROW
BEGIN
    DELETE FROM SC2
    WHERE Sno = OLD.Sno;
END //
DELIMITER ;

-- （二） 在教学管理JXGL数据库中进行如下操作：

-- 1、建立显示某系学生信息的过程

DELIMITER //
CREATE PROCEDURE DISPLAY(IN DEPARTMENT VARCHAR(40))
BEGIN
    SELECT *
    FROM STUDENT 
    WHERE SDEPT = DEPARTMENT; 
END //
DELIMITER ;

CALL DISPLAY('CS');
CALL DISPLAY('IS');
CALL DISPLAY('MA');

-- 5、创建一个计算两个整数加减乘除的函数


DELIMITER //
CREATE FUNCTION computer(x INT, y INT, c CHAR(1)) 
RETURNS INT
DETERMINISTIC
BEGIN 
   DECLARE result INT;
   IF c = '+' THEN SET result = x + y;
   ELSEIF c = '-' THEN SET result = x - y;
   ELSEIF c = '*' THEN SET result = x * y;
   ELSEIF c = '/' THEN SET result = x / y;
   ELSE SET result = NULL;
   END IF;
   RETURN result;
END //
DELIMITER ;

SELECT computer(7, 15, '+') AS result;
SELECT computer(37, 15, '-') AS result;
SELECT computer(3, 15, '*') AS result;
SELECT computer(103, 15, '/') AS result; 