-- INSERT
-- 1
CREATE TABLE EMP_ari AS SELECT * FROM employees;

CREATE TABLE DEPT_ari AS SELECT * FROM departments;

select * from emp_ari;

-- 4
ALTER TABLE emp_ari
ADD CONSTRAINT pk_emp_ari PRIMARY KEY(employee_id);
ALTER TABLE dept_ari
ADD CONSTRAINT pk_dept_ari PRIMARY KEY(department_id);
ALTER TABLE emp_ari
ADD CONSTRAINT fk_emp_dept_ari
FOREIGN KEY(department_id) REFERENCES dept_ari(department_id);

-- 5
-- a) Merge? - Nu pentru ca nu sunt toate valorile coloanelor specificate
INSERT INTO DEPT_ari
VALUES (300, 'Programare');
desc dept_ari;

-- b) Merge? - Merge dar avem valori null la coloanele ce nu apar in lista coloanelor
INSERT INTO DEPT_ari (department_id, department_name)
VALUES (300, 'Programare');
rollback;

select * from dept_ari where department_id = 300;

-- c) Merge? - Nu - conversia nu se poate face din varchar2 in number
INSERT INTO DEPT_ari (department_name, department_id)
VALUES (300, 'Programare');

-- d) Merge? - Da
INSERT INTO DEPT_ari (department_id, department_name, location_id)
VALUES (300, 'Programare', null);
rollback;

-- e) Merge? - Nu, pt ca lipseste valoarea pt PK
-- Identity insert sql server -> autogenerare valori PK
INSERT INTO DEPT_ari (department_name, location_id)
VALUES ('Programare', null);

-- 6
desc emp_ari;

insert into emp_ari(employee_id, first_name, last_name, email, hire_date, job_id, department_id)
values (207, 'Andrei', 'Riclea', 'aricle@bla.com', to_date('01-05-2020', 'DD-MM-YYYY'), 'IT_PROG', 300);

rollback;

-- 7
insert into emp_ari(employee_id, first_name, last_name, email, hire_date, job_id, department_id)
values (208, 'Andrei', 'Riclea', 'aricle@bla.com', sysdate, 'IT_PROG', 300);

rollback;

-- 8
insert into emp_ari(employee_id, first_name, last_name, email, hire_date, job_id, department_id)
values ((select max(employee_id) + 1 from emp_ari), 'Andrei', 'Riclea', 'aricle@bla.com', sysdate, 'IT_PROG', 300);

select * from emp_ari where employee_id = 207;
rollback;

-- 9
create table emp1_ari as select * from employees;

truncate table emp1_ari;

select * from emp1_ari;

insert into emp1_ari
 (select * from employees where commission_pct > 0.25); 
 
 rollback;
 
-- 10
insert into emp_ari
values (0, user, user, 'TOTAL', 'TOTAL', sysdate, 'IT_PROG', (select sum(salary) from employees), (select avg(commission_pct) from employees), null, null);

rollback;

-- 11
accept p_id prompt 'Id = ';
accept p_nume prompt 'Nume = ';
accept p_prenume prompt 'Prenume = ';
accept p_salariu prompt 'Salariu = ';
insert into emp_ari(employee_id, last_name, first_name, email, salary, job_id, hire_date)
values (&p_id, '&p_nume', '&p_prenume', concat(substr('&p_prenume', 0, 1), substr('&p_nume', 0, 7)), &p_salariu, 'IT_PROG', sysdate);

rollback;

--UPDATE
-- 14
select * from emp_ari;

update emp_ari
set salary = salary * 1.05;

rollback;

-- 15
update emp_ari
set job_id = 'SA_REP'
where department_id = 80 and commission_pct is not null;

rollback;

-- 16
update dept_ari 
set manager_id = (select employee_id from emp_ari where last_name = 'Grant' and first_name = 'Douglas')
where department_id = 20;

update emp_ari
set salary = salary + 1000
where employee_id = (select employee_id from emp_ari where last_name = 'Grant' and first_name = 'Douglas');

rollback;

-- 17
update emp_ari e1
set (salary, commission_pct) = (select salary, commission_pct from emp_ari where employee_id = e1.manager_id)
where salary = (select MIN(salary) from emp_ari);

rollback;

select * from emp_ari where salary = (select MIN(salary) from emp_ari);


-- 18
update emp_ari e1
set email = substr(last_name, 0, 1) || nvl(first_name, '.')
where salary = (select max(salary) from emp_ari where department_id = e1.department_id);

select * from emp_ari e1
where salary = (select max(salary) from emp_ari where department_id = e1.department_id);

rollback;


--DELETE

--22
-- nu merge pentru ca avem valori in emp_pnu (child values) ce referentiaza valori din dept_pnu (parent values)
delete from dept_ari;

rollback;

--23
delete from emp_ari
where commission_pct is null;

rollback;

--24
delete from dept_ari
where department_id not in (select department_id from employees where department_id is not null);

rollback;

--MERGE

-- 31
delete from emp_ari where commission_pct is null;

MERGE into emp_ari e1
using (select * from employees) e2
on (e1.employee_id = e2.employee_id)
when matched then
  update set e1.salary = e2.salary, e1.last_name = e2.last_name
when not matched then
  insert (employee_id, job_id, last_name, first_name, hire_date, email)
  values (e2.employee_id, e2.job_id, e2.last_name, e2.first_name, e2.hire_date, e2.email);
  
  
select * from emp_ari where commission_pct is not null;

