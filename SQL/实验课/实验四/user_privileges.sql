-- 用户权限管理实验 (MySQL版本)
USE JXGL3;


-- (二) 用户账户管理 (通过SQL语句模拟SQL Server管理控制台的操作)

-- 1. 创建登录名为test1的用户(密码Test1_1)，并创建数据库JXGL的用户U1
CREATE USER 'test1'@'localhost' IDENTIFIED BY '123';
-- 注意：MySQL中没有登录名和用户名的区别，直接创建用户

-- 查看初始权限
SHOW GRANTS FOR 'test1'@'localhost';

-- 登录U1查看U1权限
-- 注意：在MySQL中，我们需要切换连接来模拟登录不同用户
-- 在实际操作中，需要断开当前连接，使用test1用户重新连接
-- 以下是登录为test1后可以执行的命令：
/*
mysql -u test1 -pTest1_1
USE JXGL3;
SHOW DATABASES;
SHOW TABLES;
*/
-- 此时用户test1应该没有任何表的权限

-- 2. 赋予U1对course表的select权限，并可以传递

GRANT SELECT ON JXGL3.course TO 'test1'@'localhost' WITH GRANT OPTION;

-- 3. 登录U1查看U1权限
-- 再次使用test1用户登录，现在应该可以看到course表并有查询权限
/*
mysql -u test1 -pTest1_1
USE JXGL3;
SHOW DATABASES;
SHOW TABLES;
*/

-- 使用test1用户查看course表

SELECT * FROM JXGL3.course;


-- 尝试插入新课程（此操作会失败，因为没有INSERT权限）



INSERT INTO JXGL3.course(Cno, Cname, Cpno, Ccredit) VALUES('10', '机器学习', '5', 4);


-- 4. 删除用户U1
REVOKE ALL PRIVILEGES, GRANT OPTION FROM 'test1'@'localhost';
DROP USER 'test1'@'localhost';


SELECT *
FROM information_schema.table_privileges
WHERE table_schema = 'JXGL3'
  AND table_name = 'course';


-- (三) 通过SQL语句创建、修改、删除、查看用户账户


CREATE USER 'test2'@'localhost' IDENTIFIED BY 'Test_2';
CREATE USER 'test3'@'localhost' IDENTIFIED BY 'Test_3';


-- 3. 登录test2，查看U2权限
-- 在实际操作中，需要使用test2用户登录
/*
mysql -u test2 -pTest_2
USE JXGL3;
SHOW DATABASES;
SHOW TABLES;
*/
-- 使用管理员查看test2权限

SHOW GRANTS FOR 'test2'@'localhost';

-- 4. 给用户赋予权限
-- 给用户U2赋予student的全部权限，但不可以传播

GRANT ALL PRIVILEGES ON JXGL3.student TO 'test2'@'localhost';

-- 将sc的select权限赋予全部用户
-- MySQL不支持直接给"所有用户"授权，需要给每个用户单独授权

GRANT SELECT ON JXGL3.sc TO 'test2'@'localhost';
GRANT SELECT ON JXGL3.sc TO 'test3'@'localhost';
GRANT INSERT ON JXGL3.course TO 'test2'@'localhost' WITH GRANT OPTION;
GRANT UPDATE (Ccredit) ON JXGL3.course TO 'test2'@'localhost';

-- 5. 创建角色R1（MySQL 8.0及以上支持角色）

CREATE ROLE 'R1';
GRANT UPDATE (Ccredit) ON JXGL3.course TO 'R1';
GRANT DELETE ON JXGL3.course TO 'R1';

-- 将角色R1分配给test2
GRANT 'R1' TO 'test2'@'localhost';
SET DEFAULT ROLE 'R1' TO 'test2'@'localhost';

-- 6. 登录U2，查看U2权限
-- 在实际操作中，需要使用test2用户登录


USE JXGL3;
SHOW DATABASES;
SHOW TABLES;

-- 尝试对student插入学生

INSERT INTO student VALUES('201215166','李晓明','男',19,'IS');


UPDATE student SET Sage = 20 WHERE Sno = '201215166';
DELETE FROM student WHERE Sno = '201215166';
SELECT * FROM student;


SELECT * FROM sc;
INSERT INTO sc VALUES('201215122','1',90);


UPDATE course SET Ccredit = 5 WHERE Cname = '数据结构';

GRANT INSERT ON JXGL3.course TO 'test3'@'localhost';
GRANT UPDATE (Ccredit) ON JXGL3.course TO 'test3'@'localhost';



-- ---

-- 7. 查看U3权限

SHOW GRANTS FOR 'test3'@'localhost';

-- 8. 登录sa，回收U2的权限
-- 回收U2的course的修改学分权限
REVOKE UPDATE ON JXGL3.course FROM 'test2'@'localhost';

-- 回收U2的course的insert权限
-- MySQL中不像SQL Server那样有CASCADE和RESTRICT选项
-- MySQL的REVOKE总是级联的，会自动回收所有由该用户授予的权限

-- 回收U2的insert权限
REVOKE INSERT ON JXGL3.course FROM 'test2'@'localhost';

-- 注意：MySQL没有非级联回收权限的直接语法
-- 如果要实现类似非级联回收的效果，需要先检查是否有依赖权限，然后决定是否回收

-- 检查权限依赖的方式：
SELECT GRANTEE, PRIVILEGE_TYPE 
FROM information_schema.TABLE_PRIVILEGES 
WHERE TABLE_SCHEMA='JXGL3' 
AND TABLE_NAME='course' 
AND PRIVILEGE_TYPE='INSERT';

-- 如果希望模拟SQL Server的NON CASCADE行为，需要手动处理：
-- 1. 检查依赖关系
-- 2. 如果存在依赖权限，手动中止操作或先处理依赖权限