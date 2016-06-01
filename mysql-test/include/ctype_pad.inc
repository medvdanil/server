
--disable_warnings
drop table if exists t1;
drop table if exists t2;
--enable_warnings

#
# Unique indexes
#


eval CREATE TABLE t1 (a VARCHAR(10) PRIMARY KEY) COLLATE $coll;
INSERT INTO t1 VALUES ('abc'),('abc  '),(' a'),(' a '),('a   ');
SELECT * FROM t1 ORDER BY a;

#
# UNION
#
eval CREATE TABLE t2 (a VARCHAR(10)) COLLATE $coll;
INSERT INTO t2 VALUES ('abc '),('abc  '),(' a'),('a ');
SELECT * FROM t1 UNION SELECT * FROM t2 ORDER BY a;
DROP TABLE t1;
DROP TABLE t2;

#
# DISTINCT, COUNT, MAX
#
eval CREATE TABLE t1 (a VARCHAR(10)) COLLATE $coll;
INSERT INTO t1 VALUES ('a'),('a  '),(' a'),(' a '),('a   ');
SELECT DISTINCT * FROM t1 ORDER BY a;
SELECT DISTINCT COUNT(*) FROM t1 ORDER BY a;
SELECT MAX(a) FROM t1;

#
# GROUP BY
#
eval CREATE TABLE t2 (a VARCHAR(10), b int, c varchar(10)) COLLATE $coll;
INSERT t2 values('ab', 12, 'cd'), ('ab', 2, 'ed'), ('aa', 20, 'er'), ('aa  ', 0, 'er ');
SELECT * FROM t2 GROUP BY b ORDER BY c;
DROP TABLE t2;

#
# Weights
#
SELECT HEX(WEIGHT_STRING(a AS CHAR(10))) FROM t1;
DROP TABLE t1;

#
# IF, CASE, LEAST
#
eval SELECT IF('abc' COLLATE $coll = 'abc ' COLLATE $coll, 'pad', 'nopad');
eval SELECT CASE 'abc' COLLATE $coll WHEN 'abc ' COLLATE $coll THEN 'pad' ELSE 'nopad' END;
eval SELECT CASE WHEN 'abc' COLLATE $coll = 'abc ' COLLATE $coll THEN 'pad' ELSE 'nopad' END;
eval SELECT LEAST('abc ' COLLATE $coll, 'abc  ' COLLATE $coll);

#
# Collation mix
#
eval CREATE TABLE t1 (a VARCHAR(10)) COLLATE $coll_pad;
INSERT INTO t1 VALUES ('a'),('a ');
SELECT COUNT(*) FROM t1 WHERE a='a';
eval SELECT COUNT(*) FROM t1 WHERE a='a' COLLATE $coll_pad;
eval SELECT COUNT(*) FROM t1 WHERE a='a' COLLATE $coll;
eval ALTER TABLE t1 MODIFY a VARCHAR(10) COLLATE $coll;
SELECT COUNT(*) FROM t1 WHERE a='a';
eval SELECT COUNT(*) FROM t1 WHERE a='a' COLLATE $coll_pad;
eval SELECT COUNT(*) FROM t1 WHERE a='a' COLLATE $coll;
DROP TABLE t1;