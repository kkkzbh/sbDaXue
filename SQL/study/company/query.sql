

use company;

-- 找到所有员工
SELECT *
FROM employee;

-- 找到所有员工按薪水排序
SELECT *
FROM employee
ORDER BY salary;

SELECT *
FROM employee
ORDER BY salary DESC;

-- 别名(可省略 AS)
SELECT first_name 名,last_name 姓
FROM employee;

SELECT first_name AS 名,last_name AS 姓
FROM employee;

-- 加双引号应该是严格按引号内命名
SELECT first_name "NAME",last_name "姓"
FROM employee;

SELECT first_name NAME,last_name 姓
FROM employee;

-- 找出所有的性别
SELECT DISTINCT sex
FROM employee;

-- 查找员工的人数
SELECT COUNT(*)
FROM employee;

SELECT COUNT(emp_id)
FROM employee;

-- COUNT本质是计算实际有效值
SELECT COUNT(super_id)
FROM employee;

-- 查找1970年后出生的女性员工个数
SELECT COUNT(emp_id)
FROM employee
WHERE sex = 'F' AND birth_date > '1971-1-1';

-- 找出所有员工工资的平均值
SELECT AVG(salary)
FROM employee;

-- 找出所有男性工资的平均值
SELECT AVG(salary)
FROM employee
WHERE sex = 'M';

-- 找出有多少男性和多少女性
SELECT sex,COUNT(sex)
FROM employee
GROUP BY sex;

-- 查找每个销售员的总销售额
SELECT emp_id,SUM(total_sales)
FROM works_with
GROUP BY emp_id;

-- 查找类似LLC的client
SELECT *
FROM client
WHERE client_name LIKE '%LLC%';

-- 查找渠道供应商哪儿个在label公司
SELECT *
FROM branch_supplier
WHERE supplier_name LIKE '%label%';

-- 查找10月出生的员工
SELECT *
FROM employee
WHERE birth_date LIKE '%-10-%';

-- 查找一个list,包含first_name和branch_name
    -- UINON
    -- 1. 列数相同
    -- 2. 数据类型类似
SELECT first_name
FROM employee
UNION
SELECT branch_name
FROM branch;

-- 查找每个branch及其它主管的名字
SELECT first_name,branch_name
FROM employee
JOIN branch
ON emp_id = mgr_id;

-- 查找任何单次销售超过 30000的人

SELECT first_name,last_name
FROM employee
WHERE emp_id IN (
    SELECT emp_id
    FROM works_with
    WHERE total_sales > 30000
);

-- 查找由Michael Scott管理的所有client (假设我知道MS的id)

SELECT client_id,client_name
FROM client
WHERE branch_id IN (
    SELECT branch_id
    FROM branch
    WHERE mgr_id = 102
);



