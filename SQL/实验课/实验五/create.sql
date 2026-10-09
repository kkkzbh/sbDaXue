-- 创建数据库
CREATE DATABASE Integrity_Test;

-- 使用数据库
USE Integrity_Test;

CREATE TABLE S (
    SNO CHAR(6) PRIMARY KEY,
    SNAME CHAR(8) UNIQUE,
    CITY CHAR(20) NOT NULL
);

CREATE TABLE P (
    PNO CHAR(6) PRIMARY KEY,
    PNAME CHAR(8),
    COLOR CHAR(8),
    WEIGHT INT
);

CREATE TABLE J (
    JNO CHAR(8) PRIMARY KEY,
    JNAME CHAR(8) UNIQUE,
    CITY CHAR(20) NOT NULL
);

CREATE TABLE SPJ (
    SNO CHAR(6),
    PNO CHAR(6),
    JNO CHAR(8),
    QTY INT CHECK(QTY >= 1 AND QTY <= 1000),
    PRIMARY KEY (SNO, PNO, JNO),
    FOREIGN KEY (SNO) REFERENCES S(SNO) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY (PNO) REFERENCES P(PNO) ON UPDATE RESTRICT ON DELETE RESTRICT,
    FOREIGN KEY (JNO) REFERENCES J(JNO)
);

-- 插入示例数据到S表
INSERT INTO S VALUES
('S1', '精益', '天津'),
('S2', '盛锡', '北京'),
('S3', '东方红', '北京'),
('S4', '丰泰盛', '天津'),
('S5', '为民', '上海');

-- 插入示例数据到P表
INSERT INTO P VALUES
('P1', '螺母', '红', 12),
('P2', '螺栓', '绿', 17),
('P3', '螺丝刀', '蓝', 14),
('P4', '螺丝刀', '红', 14),
('P5', '凸轮', '蓝', 40),
('P6', '齿轮', '红', 30);

-- 插入示例数据到J表
INSERT INTO J VALUES
('J1', '三建', '北京'),
('J2', '一汽', '长春'),
('J3', '弹簧厂', '天津'),
('J4', '造船厂', '天津'),
('J5', '机车厂', '唐山'),
('J6', '无线电', '常州'),
('J7', '半导体', '南京');

-- 插入示例数据到SPJ表
INSERT INTO SPJ VALUES
('S1', 'P1', 'J1', 200),
('S1', 'P1', 'J3', 100),
('S1', 'P1', 'J4', 700),
('S1', 'P2', 'J2', 100),
('S2', 'P3', 'J1', 400),
('S2', 'P3', 'J2', 200),
('S2', 'P3', 'J4', 500),
('S2', 'P3', 'J5', 400),
('S2', 'P5', 'J1', 400),
('S2', 'P5', 'J2', 100),
('S3', 'P1', 'J1', 200),
('S3', 'P3', 'J1', 200),
('S4', 'P5', 'J1', 100),
('S4', 'P6', 'J3', 300),
('S4', 'P6', 'J4', 200),
('S5', 'P2', 'J4', 100),
('S5', 'P3', 'J1', 200),
('S5', 'P6', 'J2', 200),
('S5', 'P6', 'J4', 500);

-- 操作语句及结果分析
-- 1. 修改S表中S1元组sno为S10

UPDATE S SET SNO = 'S10' WHERE SNO = 'S1';

-- 结果：成功，由于设置了级联更新，SPJ表中所有SNO为S1的记录也会自动更新为S10

-- 2. 删除S表中S10元组

DELETE FROM S WHERE SNO = 'S10';
-- 结果：成功，由于设置了级联删除，SPJ表中所有SNO为S10的记录也会被自动删除

-- 3. 修改P表中P1元组pno为P10

UPDATE P SET PNO = 'P10' WHERE PNO = 'P1';
-- 结果：失败，因为P表的PNO在SPJ表中作为外键，设置了RESTRICT约束，无法修改已被引用的值

-- 4. 修改P表中P2元组pno为P20

UPDATE P SET PNO = 'P20' WHERE PNO = 'P2';
-- 结果：同样失败，P2在SPJ表中被引用，且设置了RESTRICT约束

-- 5. 删除P表中P10元组

DELETE FROM P WHERE PNO = 'P10';
-- 结果：操作成功，因为P10在SPJ表中未被引用

-- 6. 删除P表中P1元组

DELETE FROM P WHERE PNO = 'P1';
-- 结果：失败，因为P1在SPJ表中被引用，且设置了RESTRICT约束

-- 7. 修改J表中J1元组jno为J10


UPDATE J SET JNO = 'J10' WHERE JNO = 'J1';
-- 结果：操作失败，因为J1被SPJ表引用，且默认为RESTRICT约束

-- 8. 删除J表中J10元组

DELETE FROM J WHERE JNO = 'J10';
-- 结果：如果J10在数据库中存在且未被引用，操作成功；否则失败

-- 9. 删除J表中J1元组

DELETE FROM J WHERE JNO = 'J1';
-- 结果：操作失败，因为J1在SPJ表中被引用，且外键约束为RESTRICT