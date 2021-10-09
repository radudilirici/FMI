--1
CREATE OR REPLACE TRIGGER trig1_mng
      BEFORE INSERT OR UPDATE OR DELETE ON emp_mng
BEGIN
 IF (TO_CHAR(SYSDATE,'D') = 1) 
     OR (TO_CHAR(SYSDATE,'HH24') NOT BETWEEN 8 AND 17)
 THEN
    RAISE_APPLICATION_ERROR(-20001,'tabelul nu poate fi actualizat');
 END IF;
END;
/

delete from emp_mng where employee_id< 102;
ROLLBACK;

select TO_CHAR(SYSDATE,'HH24')
from dual;

DROP TRIGGER trig1_mng;

--2
--Varianta 1
CREATE OR REPLACE TRIGGER trig21_mng
  BEFORE UPDATE OF salary ON emp_mng
  FOR EACH ROW
BEGIN
  IF (:NEW.salary < :OLD.salary) THEN 
     RAISE_APPLICATION_ERROR(-20002,'salariul nu poate fi micsorat');
  END IF;
END;
/

UPDATE emp_mng
SET    salary = salary-100;
rollback;
DROP TRIGGER trig21_mng;

--Varianta 2
CREATE OR REPLACE TRIGGER trig22_mng
  BEFORE UPDATE OF salary ON emp_mng
  FOR EACH ROW
  WHEN (NEW.salary < OLD.salary)
BEGIN
  RAISE_APPLICATION_ERROR(-20002,'salariul nu poate fi micsorat');
END;
/

UPDATE emp_mng
SET    salary = salary-100;
DROP TRIGGER trig22_mng;

--3
drop table job_grades_mng;
drop table emp_mng;
create table emp_mng as select * from employees;
create table job_grades_mng as select * from job_grades;

select * from job_grades_mng;

1	2000	5000
2	5001	7000
3	7001	10000
4	10001	13000
5	13001	16000
6	16001	19000
7	19001	99000

  SELECT MIN(salary), MAX(salary)
  FROM   emp_mng;
  
  --2100	24000

CREATE OR REPLACE TRIGGER trig3_mng
  BEFORE UPDATE OF lowest_sal, highest_sal ON job_grades_mng
  FOR EACH ROW
DECLARE
  v_min_sal  emp_mng.salary%TYPE;
     v_max_sal  emp_mng.salary%TYPE;
  exceptie EXCEPTION;
  exceptie1 EXCEPTION;
  exc Exception;
BEGIN
  SELECT MIN(salary), MAX(salary)
  INTO   v_min_sal,v_max_sal
  FROM   emp_mng;
  IF (:OLD.grade_level=1) AND  (v_min_sal< :NEW.lowest_sal) 
     THEN RAISE exceptie1;
  END IF;
  IF (:OLD.grade_level=7) AND  (v_max_sal> :NEW.highest_sal) 
     THEN RAISE exceptie;
  END IF;
  if (:new.lowest_sal> :OLD.HIGHEST_SAL) OR (:OLD.LOWEST_SAL > :NEW.HIGHEST_SAL)
      then raise exc;
      end if;
EXCEPTION
  WHEN exceptie1 THEN
    RAISE_APPLICATION_ERROR (-20003, 'Exista salarii care se gasesc in afara intervalului(lim_inf)'); 
 WHEN exceptie THEN
    RAISE_APPLICATION_ERROR (-20003, 'Exista salarii care se gasesc in afara intervalului(lim_sup)'); 
  WHEN exc THEN
    RAISE_APPLICATION_ERROR (-20003, 'Exista salarii care se gasesc in afara intervalului TOATE'); 
END;
/
update job_grades_mng
set  highest_sal =1000
where grade_level=1;

UPDATE job_grades_mng 
SET    lowest_sal =3000
WHERE  grade_level=1;

UPDATE job_grades_mng
SET    highest_sal =20000  --:old.grade_lavel =7  :old.highest_sal= 99000
WHERE  grade_level=7;                         --  :new.highest_sal =20000



UPDATE job_grades_mng 
SET    lowest_sal =5001
WHERE  grade_level=2;

UPDATE job_grades_mng 
SET    highest_sal =0
WHERE  grade_level=1;

select * from job_grades_mng;

DROP TRIGGER trig3_mng;

--4
drop table info_dept_mng2;
create table  info_dept_mng2
(id number(3) primary key,
nume_dept varchar2(50),
plati number);

insert into info_dept_mng2
select max(department_id), department_name, nvl(sum(salary),0)
from departments
left outer join employees
using (department_id)
group by department_name;


CREATE OR REPLACE PROCEDURE modific_plati_mng
          (v_codd  info_dept_mng2.id%TYPE,
           v_plati info_dept_mng2.plati%TYPE) AS
BEGIN
  UPDATE  info_dept_mng2
  SET     plati = NVL (plati, 0) + v_plati
  WHERE   id = v_codd;
END;
/

CREATE OR REPLACE TRIGGER trig4_mng
  AFTER DELETE OR UPDATE  OR  INSERT OF salary ON emp_mng
  FOR EACH ROW
BEGIN
  IF DELETING THEN 
     -- se sterge un angajat
     modific_plati_mng (:OLD.department_id, -1*:OLD.salary);
  ELSIF UPDATING THEN 
    --se modifica salariul unui angajat
    modific_plati_mng(:OLD.department_id,:NEW.salary-:OLD.salary);  
  ELSE 
    -- se introduce un nou angajat
    modific_plati_mng(:NEW.department_id, :NEW.salary);
  END IF;
END;
/

SELECT * FROM  info_dept_mng2 WHERE id=90;

--90	Executive	56000

INSERT INTO emp_mng (employee_id, last_name, email, hire_date, 
                     job_id, salary, department_id) 
VALUES (300, 'N1', 'n1@g.com',sysdate, 'SA_REP', 2000, 90);

SELECT * FROM  info_dept_mng2 WHERE id=90;
--90	Executive	58000

UPDATE emp_mng
SET    salary = salary + 1000
WHERE  employee_id=300;

SELECT * FROM  info_dept_mng2 WHERE id=90;
--90	Executive	59000

DELETE FROM emp_mng
WHERE  employee_id=300;   

SELECT * FROM  info_dept_mng2 WHERE id=90;
--90	Executive	56000

DROP TRIGGER trig4_mng;

--5

create table info_emp_mng2
(id number(3) primary key,
nume varchar2(50),
prenume varchar2(50),
salariu number(6),
id_dept number(3) references info_dept_mng(id));

insert into info_emp_mng2
select employee_id, last_name, first_name, salary, department_id
from  employees;

CREATE OR REPLACE VIEW v_info_mng AS
  SELECT e.id, e.nume, e.prenume, e.salariu, e.id_dept, 
         d.nume_dept, d.plati 
  FROM   info_emp_mng2 e, info_dept_mng2 d
  WHERE  e.id_dept = d.id;

SELECT *
FROM   user_updatable_columns
WHERE  table_name = UPPER('v_info_mng');

CREATE OR REPLACE TRIGGER trig5_mng
    INSTEAD OF INSERT OR DELETE OR UPDATE ON v_info_mng
    FOR EACH ROW
BEGIN
IF INSERTING THEN 
    -- inserarea in vizualizare determina inserarea 
    -- in info_emp_mng2 si reactualizarea in info_dept_mng2
    -- se presupune ca departamentul exista
   INSERT INTO info_emp_mng2 
   VALUES (:NEW.id, :NEW.nume, :NEW.prenume, :NEW.salariu,
           :NEW.id_dept);
     
   UPDATE info_dept_mng2
   SET    plati = plati + :NEW.salariu
   WHERE  id = :NEW.id_dept;

ELSIF DELETING THEN
   -- stergerea unui salariat din vizualizare determina
   -- stergerea din info_emp_mng2 si reactualizarea in
   -- info_dept_mng2
   DELETE FROM info_emp_mng2
   WHERE  id = :OLD.id;
     
   UPDATE info_dept_mng2
   SET    plati = plati - :OLD.salariu
   WHERE  id = :OLD.id_dept;

ELSIF UPDATING ('salariu') THEN
   /* modificarea unui salariu din vizualizare determina 
      modificarea salariului in info_emp_mng2 si reactualizarea
      in info_dept_mng2    */
    	
   UPDATE  info_emp_mng2
   SET     salariu = :NEW.salariu
   WHERE   id = :OLD.id;
    	
   UPDATE info_dept_mng2
   SET    plati = plati - :OLD.salariu + :NEW.salariu
   WHERE  id = :OLD.id_dept;

ELSIF UPDATING ('id_dept') THEN
    /* modificarea unui cod de departament din vizualizare
       determina modificarea codului in info_emp_mng2 
       si reactualizarea in info_dept_mng2  */  
    UPDATE info_emp_mng2
    SET    id_dept = :NEW.id_dept
    WHERE  id = :OLD.id;
    
    UPDATE info_dept_mng2
    SET    plati = plati - :OLD.salariu
    WHERE  id = :OLD.id_dept;
    	
    UPDATE info_dept_mng2
    SET    plati = plati + :NEW.salariu
    WHERE  id = :NEW.id_dept;
  END IF;
END;
/

SELECT *
FROM   user_updatable_columns
WHERE  table_name = UPPER('v_info_mng');


SELECT * FROM  info_dept_mng2 WHERE id=10;
--10	Administration	4400

-- adaugarea unui nou angajat
INSERT INTO v_info_mng 
VALUES (400, 'N1', 'P1', 3000,10, 'Nume dept', 0);

SELECT * FROM  info_emp_mng2 WHERE id=400;
SELECT * FROM  info_dept_mng2 WHERE id=10;
--10	Administration	7400

-- modificarea salariului unui angajat
UPDATE v_info_mng
SET    salariu=salariu + 1000
WHERE  id=400;

SELECT * FROM  info_emp_mng2 WHERE id=400;
--400	N1	P1	4000	10
SELECT * FROM  info_dept_mng2 WHERE id=10;
--10	Administration	8400

-- modificarea departamentului unui angajat
SELECT * FROM  info_dept_mng2 WHERE id=90;
--90	Executive	58000

UPDATE v_info_mng
SET    id_dept=90
WHERE  id=400;

SELECT * FROM  info_emp_mng2 WHERE id=400;
--400	N1	P1	4000	90
SELECT * FROM  info_dept_mng2 WHERE id IN (10,90);
--10	Administration	4400
--90	Executive	62000

-- eliminarea unui angajat
DELETE FROM v_info_mng WHERE id = 400;
SELECT * FROM  info_emp_mng2 WHERE id=400;
SELECT * FROM  info_dept_mng2 WHERE id = 90;
--90	Executive	58000

DROP TRIGGER trig5_mng;

--6 
CREATE OR REPLACE TRIGGER trig6_mng
  BEFORE DELETE ON emp_mng
 BEGIN
  IF USER= UPPER('grupamng') THEN
     RAISE_APPLICATION_ERROR(-20900,'Nu ai voie sa stergi!');
  END IF;
 END;
/

DROP TRIGGER trig6_mng;

--7
CREATE TABLE audit_mng
   (utilizator     VARCHAR2(30),
    nume_bd        VARCHAR2(50),
    eveniment      VARCHAR2(20),
    nume_obiect    VARCHAR2(30),
    data           DATE);
CREATE OR REPLACE TRIGGER trig7_mng
  AFTER CREATE OR DROP OR ALTER ON SCHEMA
BEGIN
  INSERT INTO audit_mng
  VALUES (SYS.LOGIN_USER, SYS.DATABASE_NAME, SYS.SYSEVENT, 
          SYS.DICTIONARY_OBJ_NAME, SYSDATE);
END;
/

CREATE INDEX ind_mng ON info_emp_mng2(nume);
DROP INDEX ind_mng;
SELECT * FROM audit_mng;

DROP TRIGGER trig7_mng;

--8
CREATE OR REPLACE PACKAGE pachet_mng
AS
	smin emp_mng.salary%type;
	smax emp_mng.salary%type;
	smed emp_mng.salary%type;
END pachet_mng;
/

CREATE OR REPLACE TRIGGER trig81_mng
BEFORE UPDATE OF salary ON emp_mng
BEGIN
  SELECT MIN(salary),AVG(salary),MAX(salary)
  INTO pachet_mng.smin, pachet_mng.smed, pachet_mng.smax
  FROM emp_mng;
END;
/

CREATE OR REPLACE TRIGGER trig82_mng
BEFORE UPDATE OF salary ON emp_mng
FOR EACH ROW
BEGIN
IF(:OLD.salary=pachet_mng.smin)AND (:NEW.salary>pachet_mng.smed) 
 THEN
   RAISE_APPLICATION_ERROR(-20001,'Acest salariu depaseste valoarea medie');
ELSIF (:OLD.salary= pachet_mng.smax) 
       AND (:NEW.salary<  pachet_mng.smed) 
 THEN
   RAISE_APPLICATION_ERROR(-20001,'Acest salariu este sub valoarea medie');
END IF;
END;
/

SELECT AVG(salary)
FROM   emp_mng;

UPDATE emp_mng 
SET    salary=10000 
WHERE  salary=(SELECT MIN(salary) FROM emp_mng);

UPDATE emp_mng 
SET    salary=1000 
WHERE  salary=(SELECT MAX(salary) FROM emp_mng);

DROP TRIGGER trig81_mng;
DROP TRIGGER trig82_mng;
