--lab 4 PLSQL
   
--1
DECLARE
  v_nume employees.last_name%TYPE := Initcap('&p_nume');   

  FUNCTION f1 RETURN NUMBER IS
    salariu employees.salary%type; 
  BEGIN
    SELECT salary INTO salariu 
    FROM   employees
    WHERE  last_name = v_nume;
    RETURN salariu;
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
       DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
       DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
       DBMS_OUTPUT.PUT_LINE('Alta eroare!');
  END f1;
BEGIN
  DBMS_OUTPUT.PUT_LINE('Salariul este '|| f1);

EXCEPTION
  WHEN OTHERS THEN
    DBMS_OUTPUT.PUT_LINE('Eroarea are codul = '||SQLCODE
            || ' si mesajul = ' || SQLERRM);
END;
/
--Bell, King, Kimball

--Salariul este 4000
--
--Exista mai multi angajati cu numele dat
--Eroarea are codul = -6503 si mesajul = ORA-06503: PL/SQL: Function returned without value
--
--Exista mai multi angajati cu numele dat
--
--Nu exista angajati cu numele dat
--Eroarea are codul = -6503 si mesajul = ORA-06503: PL/SQL: Function returned without value


--2
CREATE OR REPLACE FUNCTION f2_mng 
  (v_nume employees.last_name%TYPE DEFAULT 'Bell')    
RETURN NUMBER IS
    salariu employees.salary%type; 
  BEGIN
    SELECT salary INTO salariu 
    FROM   employees
    WHERE  last_name = v_nume;
    RETURN salariu;
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
       RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
       RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
       RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
END f2_mng;
/

-- metode de apelare
-- bloc plsql
BEGIN
  DBMS_OUTPUT.PUT_LINE('Salariul este '|| f2_mng);
END;
/

BEGIN
  DBMS_OUTPUT.PUT_LINE('Salariul este '|| f2_mng('King'));
END;
/

-- SQL
  SELECT f2_mng FROM DUAL;
  SELECT f2_mng('King') FROM DUAL;

-- SQL*PLUS CU VARIABILA HOST
  VARIABLE nr NUMBER
  EXECUTE :nr := f2_mng('Bell');
  PRINT nr
  
--  NR
------
--4000

-- 3 
-- varianta 1
DECLARE
  v_nume employees.last_name%TYPE := Initcap('&p_nume');   
  
  PROCEDURE p3 
  IS 
      salariu employees.salary%TYPE;
  BEGIN
    SELECT salary INTO salariu 
    FROM   employees
    WHERE  last_name = v_nume;
    DBMS_OUTPUT.PUT_LINE('Salariul este '|| salariu);
  
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
       DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
       DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
       DBMS_OUTPUT.PUT_LINE('Alta eroare!');
  END p3;

BEGIN
  p3;
END;
/

-- varianta 2
DECLARE
  v_nume employees.last_name%TYPE := Initcap('&p_nume');  
  v_salariu employees.salary%type;

  PROCEDURE p3(salariu OUT employees.salary%type) IS 
  BEGIN
    SELECT salary INTO salariu 
    FROM   employees
    WHERE  last_name = v_nume;
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
       RAISE_APPLICATION_ERROR(-20000,'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
       RAISE_APPLICATION_ERROR(-20001,'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
       RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
  END p3;

BEGIN
  p3(v_salariu);
  DBMS_OUTPUT.PUT_LINE('Salariul este '|| v_salariu);
END;
/
 
--4
-- varianta 1
CREATE OR REPLACE PROCEDURE p4_mng
      (v_nume employees.last_name%TYPE)
  IS 
      salariu employees.salary%TYPE;
  BEGIN
    SELECT salary INTO salariu 
    FROM   employees
    WHERE  last_name = v_nume;
    DBMS_OUTPUT.PUT_LINE('Salariul este '|| salariu);
  
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
       RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
       RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
       RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
  END p4_mng;
/

-- metode apelare
-- 1. Bloc PLSQL
BEGIN
  p4_mng('Bell');
END;
/

-- 2. SQL*PLUS
EXECUTE p4_mng('Bell');
EXECUTE p4_mng('King');
EXECUTE p4_mng('Kimball');

-- varianta 2
CREATE OR REPLACE PROCEDURE 
       p4_mng(v_nume IN employees.last_name%TYPE,
               salariu OUT employees.salary%type) IS 
  BEGIN
    SELECT salary INTO salariu 
    FROM   employees
    WHERE  last_name = v_nume;
  EXCEPTION
    WHEN NO_DATA_FOUND THEN
       RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
       RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
       RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
  END p4_mng;
/

-- metode apelare
-- Bloc PLSQL
DECLARE
   v_salariu employees.salary%type;
BEGIN
  p4_mng('Bell',v_salariu);
  DBMS_OUTPUT.PUT_LINE('Salariul este '|| v_salariu);
END;
/

-- SQL*PLUS
VARIABLE v_sal NUMBER
EXECUTE p4_mng ('Bell',:v_sal)
PRINT v_sal

--5
VARIABLE ang_man NUMBER
BEGIN
 :ang_man:=200;
END;
/

CREATE OR REPLACE PROCEDURE p5_mng  (nr IN OUT NUMBER) IS 
BEGIN
 SELECT manager_id INTO nr
 FROM employees
 WHERE employee_id=nr;
END p5_mng;
/

EXECUTE p5_mng (:ang_man)
PRINT ang_man

PROCEDURE P5_MNG compiled
anonymous block completed
ANG_MAN
---
101

anonymous block completed
ANG_MAN
---
100

anonymous block completed
ANG_MAN
------


--6
DECLARE
nume employees.last_name%TYPE;
PROCEDURE p6 (rezultat OUT employees.last_name%TYPE,
              comision IN  employees.commission_pct%TYPE:=NULL,
              cod      IN  employees.employee_id%TYPE:=NULL) 
 IS
 BEGIN
 IF (comision IS NOT NULL) THEN
    SELECT last_name 
    INTO rezultat
    FROM employees
    WHERE commission_pct= comision;
    DBMS_OUTPUT.PUT_LINE('numele salariatului care are comisionul ' 
                        ||comision||' este '||rezultat);
 ELSE 
    SELECT last_name 
    INTO rezultat
    FROM employees
    WHERE employee_id =cod;
    DBMS_OUTPUT.PUT_LINE('numele salariatului avand codul ' ||cod||' este '||rezultat);
 END IF;
END p6;

BEGIN
  p6(nume,0.4);
  p6(nume,0.4,null);
  p6(nume,0.4,200);
  p6(nume,cod=>200);
  p6(nume,null,200);
END;
/

--7
DECLARE
  medie1 NUMBER(10,2);
  medie2 NUMBER(10,2);
  FUNCTION medie (v_dept employees.department_id%TYPE) 
    RETURN NUMBER IS
    rezultat NUMBER(10,2);
  BEGIN
    SELECT AVG(salary) 
    INTO   rezultat 
    FROM   employees
    WHERE  department_id = v_dept;
    RETURN rezultat;
  END;
  
  FUNCTION medie (v_dept employees.department_id%TYPE,
                  v_job employees.job_id %TYPE) 
    RETURN NUMBER IS
    rezultat NUMBER(10,2);
  BEGIN
    SELECT AVG(salary) 
    INTO   rezultat 
    FROM   employees
    WHERE  department_id = v_dept AND job_id = v_job;
    RETURN rezultat;
  END;

BEGIN
  medie1:=medie(80);
  DBMS_OUTPUT.PUT_LINE('Media salariilor din departamentul 80' 
      || ' este ' || medie1);
  medie2 := medie(80,'SA_MAN');
  DBMS_OUTPUT.PUT_LINE('Media salariilor managerilor din'
      || ' departamentul 80 este ' || medie2);
END;
/

select * from employees where department_id =80;
select * from employees where department_id =80 and job_id='SA_MAN';

--8
CREATE OR REPLACE FUNCTION factorial_mng(n NUMBER) 
 RETURN INTEGER 
 IS
 BEGIN
  IF (n=0) THEN RETURN 1;
  ELSE RETURN n*factorial_mng(n-1);
  END IF;
END factorial_mng;
/

--9
CREATE OR REPLACE FUNCTION medie_mng 
RETURN NUMBER 
IS 
rezultat NUMBER;
BEGIN
  SELECT AVG(salary) INTO   rezultat
  FROM   employees;
  RETURN rezultat;
END;
/
SELECT last_name,salary
FROM   employees
WHERE  salary >= medie_mng;




DECLARE
v_id employees.employee_id%TYPE;
v_last_name employees.last_name%TYPE;
v_job job_history.job_id%TYPE;
 
cursor c is select employee_id, last_name, max(employees.job_id)
            from job_history
            inner join employees using (employee_id)
            group by employee_id,last_name
            having count(1) =   ( select max(count(1))
                        from job_history
                        group by employee_id);
 cursor cursor_j(id employees.employee_id%type) is
      select job_id
      from job_history
      where employee_id = id;
PROCEDURE p IS 
    begin
    OPEN c;
    LOOP
    FETCH c INTO v_id,v_last_name, v_job; 
    EXIT WHEN c%NOTFOUND; 
    DBMS_OUTPUT.PUT_LINE(v_id ||' '|| v_last_name ||' '|| v_job );
      for i in cursor_j(v_id) loop
           DBMS_OUTPUT.PUT_LINE(i.job_id);
           end loop;
    end loop;
    close c;

END p;
 
BEGIN
p;
END;
/


create or replace type inf is object
(cod number(3),
nume varchar2(40),
job varchar2(20))

create or replace type tabel_aux is table of inf;
/
create or replace function afiseazaInformatii
return tabel_aux
is
x tabel_aux;
begin
select inf(employee_id, last_name, job_id) bulk collect into x from employees
where employee_id in (
select ee.employee_id ee from employees ee join job_history hh on (hh.employee_id = ee.employee_id)
group by ee.employee_id having count(hh.job_id) = (
select max(count(h.job_id)) from employees e join job_history h on (h.employee_id = e.employee_id) group by e.employee_id));
return x;
end;
/

declare
k tabel_aux;
begin
k := afiseazaInformatii ;
for i in 1..k.count loop
dbms_output.put_line(k(i).nume || ' ' || k(i).job);
end loop;
end;
/



alter table emp_mng
add next_sef number;

CREATE OR REPLACE PROCEDURE ex4
is 
    nr employees.employee_id%TYPE;
    mgn employees.employee_id%TYPE;
    type tip_cod is varray(200) of employees.employee_id%type;
    coduri tip_cod;
BEGIN
    select employee_id bulk collect into coduri
    from employees
    where manager_id is not null;
    for i in coduri.first ..coduri.last loop 

        select employee_id into nr 
        from (select employee_id 
              from employees 
              where manager_id = (select manager_id 
                                  from employees
                                  where employee_id = coduri(i)) 
              order by hire_date)
              where rownum<2;

              update emp_mng
              set next_sef = nr
              where employee_id = coduri(i);

    end loop;   

EXCEPTION 
WHEN NO_DATA_FOUND THEN  dbms_output.put_line ('Nu exista manager pentru angajatul dat');
 
END ex4;
/
 
BEGIN
    ex4();
END;
/
select *
from    emp_mng;



create or replace PROCEDURE p IS 
        
        v_id employees.employee_id%TYPE;
        v_last_name employees.last_name%TYPE;
        v_job job_history.job_id%TYPE;
         
        cursor c is select employee_id, last_name, max(employees.job_id)
                    from job_history
                    inner join employees using (employee_id)
                    group by employee_id,last_name
                    having count(1) =   ( select max(count(1))
                                from job_history
                                group by employee_id);
         cursor cursor_j(id employees.employee_id%type) is
              select job_id
              from job_history
              where employee_id = id;
begin
    OPEN c;
    LOOP
    FETCH c INTO v_id,v_last_name, v_job; 
    EXIT WHEN c%NOTFOUND; 
    DBMS_OUTPUT.PUT_LINE(v_id ||' '|| v_last_name ||' '|| v_job );
      for i in cursor_j(v_id) loop
           DBMS_OUTPUT.PUT_LINE(i.job_id);
           end loop;
    end loop;
    close c;

END p;
/
 
BEGIN
p;
END;
/



create or replace procedure intoarceCod(cod_ang IN OUT employees.employee_id%type)
is
type vect is varray(140) of number;
t vect := vect();
ok number := 0;
begin
select employee_id bulk collect into t from employees order by hire_date;

for i in 1..t.count loop
if t(i)=cod_ang and ok =0 then
cod_ang := t.count - i;
ok := 1;
end if;
end loop;
end;
/


declare
v_cod number(4) := &p_cod ;
begin
intoarceCod (v_cod);
dbms_output.put_line(v_cod);
end;
/



CREATE OR REPLACE PROCEDURE p3(
    cod IN OUT NUMBER )
IS
BEGIN
  SELECT employee_id
  INTO cod
  FROM
    (SELECT employee_id,
      hire_date
    FROM employees
    WHERE hire_date >
      ( SELECT hire_date FROM employees WHERE employee_id = cod
      )
    ORDER BY 2
    )
  WHERE ROWNUM < 2;
EXCEPTION
WHEN no_data_found THEN
  raise_application_error(-20001, 'ANGAJATUL CU CODUL DAT A FOST ANGAJAT ULTIMUL');
END p3;
/


 DECLARE 
    v_id employees.employee_id%TYPE;
 
    PROCEDURE ang_dupa
        (v_id IN OUT employees.employee_id%TYPE)
    IS 
     data employees.hire_date%type;
    BEGIN
   
    sELECT hire_date
    into data
    FROM employees
    WHERE employee_id = v_id;
        SELECT count(employee_id)
        INTO v_id
        FROM employees
        WHERE hire_date> DATA; 
    END ang_dupa;

BEGIN

    v_id := 136;

    DBMS_OUTPUT.PUT_LINE(v_id);
 
    ang_dupa(v_id);

    DBMS_OUTPUT.PUT_LINE(v_id);
 
END;
/


DECLARE 
    v_id employees.employee_id%TYPE;
 
    PROCEDURE ang_dupa
        (v_id IN OUT employees.employee_id%TYPE)
    IS BEGIN
        SELECT COUNT(employee_id)
        INTO v_id
        FROM employees
        WHERE hire_date >(SELECT hire_date
                FROM employees
                WHERE employee_id = v_id); 
    END ang_dupa;

BEGIN

    v_id := 136;

    DBMS_OUTPUT.PUT_LINE(v_id);
 
    ang_dupa(v_id);

    DBMS_OUTPUT.PUT_LINE(v_id);
 
END;
/


DECLARE 
    v_id employees.employee_id%TYPE;
 
    PROCEDURE ang_dupa
        (v_id IN OUT employees.employee_id%TYPE)
    IS BEGIN
    SELECT EMPLOYEE_ID
    INTO V_ID
    FROM(
        SELECT Employee_id
        FROM employees
        WHERE hire_date >(SELECT hire_date
                FROM employees
                WHERE employee_id = v_id)
        ORDER BY HIRE_DATE)
        WHERE ROWNUM =1;
    END ang_dupa;

BEGIN

    v_id := 136;

    DBMS_OUTPUT.PUT_LINE(v_id);
 
    ang_dupa(v_id);

    DBMS_OUTPUT.PUT_LINE(v_id);
 
END;
/



DECLARE
    TYPE tablou_employee_id IS
        TABLE OF employees.employee_id%TYPE INDEX BY BINARY_INTEGER;
    TYPE tablou_first_name IS
        TABLE OF employees.first_name%TYPE INDEX BY BINARY_INTEGER;
    TYPE tablou_job_id IS
        TABLE OF employees.job_id%TYPE INDEX BY BINARY_INTEGER;
    z_employee_id  tablou_employee_id;
    z_first_name   tablou_first_name;
    z_job_id       tablou_job_id;

PROCEDURE findmin (
        c_employee_id  OUT  tablou_employee_id,
        c_first_name   OUT  tablou_first_name,
        c_job_id       OUT  tablou_job_id
    ) IS
    BEGIN
        SELECT
            employee_id,
            first_name,
            job_id
        BULK COLLECT
        INTO
            c_employee_id,
            c_first_name,
            c_job_id
        FROM
            employees
        WHERE
            employee_id IN (
                SELECT
                    employee_id
                FROM
                    job_history
                GROUP BY
                    employee_id
                HAVING
                    COUNT(*) = (
                        SELECT
                            MAX(cnt)
                        FROM
                            (
                                SELECT
                                    COUNT(*) cnt
                                FROM
                                    job_history
                                GROUP BY
                                    employee_id
                            )
                    )
            );

    END;

BEGIN
    findmin(z_employee_id, z_first_name, z_job_id);
    FOR i IN z_employee_id.FIRST..z_employee_id.LAST LOOP
        DBMS_OUTPUT.put_line(z_employee_id(i)
                             || z_first_name(i)
                             || z_job_id(i));
    END LOOP;

END;
/


CREATE OR REPLACE PROCEDURE p6 (
n1 OUT NUMBER,
n2 OUT NUMBER
) IS
BEGIN

UPDATE EMPLOYEES
SET SALARY = SALARY * 1.01
WHERE DEPARTMENT_ID IN (select department_id
from employees
group by department_id
HAVING COUNT(EMPLOYEE_ID) > 5);

n1 := SQL%ROWCOUNT;

UPDATE EMPLOYEES
SET SALARY = SALARY * 0.99
WHERE DEPARTMENT_ID not IN (select department_id
from employees
group by department_id
HAVING COUNT(EMPLOYEE_ID) > 5);

n2 := SQL%ROWCOUNT;



END p6;




declare
nr1 number;
nr2 number;
begin
p6(nr1, nr2);
dbms_output.put_line(nr1);
dbms_output.put_line(nr2);
end;