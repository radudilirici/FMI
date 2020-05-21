-- 1
create table emp_rdi as select * from employees;
create table dept_rdi as select * from departments;

-- 2
desc empoyees;
desc emp_rdi;
desc departments;
desc desc_rdi;

-- 3
select * from emp_rdi;
select * from dept_rdi;

-- 12
create table emp1_rdi as select * from employees
where 1 = 2;
create table emp2_rdi as select * from employees
where 1 = 2;
create table emp3_rdi as select * from employees
where 1 = 2;

insert into emp1_rdi
    (select * from employees where salary < 5000); 
select * from emp1_rdi;
rollback;

insert into emp2_rdi
    (select * from employees where salary >= 5000 and salary <= 10000); 
select * from emp2_rdi;
rollback;

insert into emp3_rdi
    (select * from employees where salary > 10000); 
select * from emp3_rdi;
rollback;

-- 13
create table emp0_rdi as select * from employees
where 1 = 2;

insert into emp0_rdi
    (select * from employees where department_id = 80);
    
insert into emp1_rdi
    (select * from employees where salary < 5000 and department_id != 80); 
select * from emp1_rdi;
rollback;

insert into emp2_rdi
    (select * from employees where salary >= 5000 and salary <= 10000 and department_id != 80); 
select * from emp2_rdi;
rollback;

insert into emp3_rdi
    (select * from employees where salary > 10000 and department_id != 80); 
select * from emp3_rdi;

-- 19
update emp_rdi e1
set salary = (select avg(salary) from emp_rdi)
where hire_date = (select max(hire_date) from employees where department_id = e1.department_id);

select * from emp_rdi;
rollback;

-- 20
update emp_rdi
set (job_id, department_id) = (select job_id, department_id from employees where employee_id = 205)
where employee_id = 114;
select * from emp_rdi;

-- 21
accept p_id prompt 'deptartment_id = '
select * from dept_rdi where department_id = &p_id;
accept p_name prompt 'department_name = ';
accept p_mng prompt 'manager_id = ';
accept p_loc prompt 'location_id = ';
update dept_rdi
set (department_name, manager_id, location_id) = (select '&p_name', '&p_mng', '&p_loc' from dual)
where department_id = &p_id;

-- 25
accept p_id prompt 'id = ';
select * from emp_rdi where employee_id = &p_id;
delete from emp_rdi
where employee_id = &p_id;

select * from emp_rdi;

-- 26
accept p_id prompt 'Id = ';
accept p_nume prompt 'Nume = ';
accept p_prenume prompt 'Prenume = ';
accept p_salariu prompt 'Salariu = ';
insert into emp_rdi(employee_id, last_name, first_name, email, salary, job_id, hire_date)
values (&p_id, '&p_nume', '&p_prenume', concat(substr('&p_prenume', 0, 1), substr('&p_nume', 0, 7)), &p_salariu, 'IT_PROG', sysdate);

commit; -- pt exercitiul 29
-- 27 ????

-- 28
delete from emp_rdi
where 1 = 1;
select * from emp_rdi;

-- 29
rollback; -- am dat commit la ex 26

-- 30
select * from emp_rdi;
commit;