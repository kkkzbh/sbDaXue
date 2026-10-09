USE homework;

-- (1) 求供应工程J1零件的供应商号码SNO
SELECT DISTINCT SNO
FROM SPJ
WHERE JNO = 'J1';

-- (2) 求供应工程J1零件P1的供应商号码SNO
SELECT DISTINCT SNO
FROM SPJ
WHERE PNO = 'P1'
  AND JNO = 'J1';

-- (3) 求供应工程J1零件为红色的供应商号码SNO
SELECT DISTINCT SPJ.SNO
FROM SPJ,P 
WHERE P.COLOR = '红' 
  AND SPJ.JNO = 'J1'
  AND SPJ.PNO = P.PNO;

-- (4) 求没有使用天津供应商生产的红色零件的工程号JNO

SELECT JNO
FROM J x
WHERE NOT EXISTS(
    SELECT JNO
    FROM SPJ,S,P
    WHERE SPJ.SNO = S.SNO AND
          SPJ.PNO = P.PNO AND
          S.CITY = '天津' AND
          P.COLOR = '红' AND
          x.JNO = SPJ.JNO
);

-- (5) 求至少用了供应商S1所供应的全部零件的工程号JNO

SELECT JNO
FROM J
WHERE NOT EXISTS (
    SELECT DISTINCT PNO
    FROM SPJ x
    WHERE SNO = 'S1' AND
         NOT EXISTS (
              SELECT DISTINCT PNO
              FROM SPJ y
              WHERE y.JNO = J.JNO AND
                    y.PNO = x.PNO
          )
);
