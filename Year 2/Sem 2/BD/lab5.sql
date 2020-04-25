-- 2
-- a)
select department_name, job_title, avg(salary)
from employees
join departments using(department_id)
join jobs using(job_id)
group by cube(department_name, job_title);
-- b)
select department_name, job_title, avg(salary), 
case when grouping(department_name) = 0 and grouping(job_title) = 0 then 'Dep si Job'
when grouping(department_name) = 0 then 'Dep'
when grouping(job_title) = 0 then 'Job'
else '-' end "Intervenite"
from employees
join departments using(department_id)
join jobs using(job_id)
group by cube(department_name, job_title);

-- 4
select department_name, job_title, e.manager_id, 
case when avg(salary) > 15000 then round(avg(salary), 2)
else null end avg_salary
from employees e
join departments using (department_id)
join jobs using (job_id)
group by grouping sets ((department_name, job_title), (job_title, e.manager_id), ());

-- 5
-- a)
select e1.employee_id, e1.last_name, e1.department_id, e1.salary, round(e2."avg") "Salariu mediu"
from employees e1
join (select department_id, avg(salary) "avg"
      from employees
      group by department_id) e2 
on (e1.department_id = e2.department_id and e1.salary > e2."avg");
-- b)
select e1.employee_id, e1.last_name, e1.department_id, e1.salary, round(e2."avg") "Salariu mediu"
from (select department_id, avg(salary) "avg"
      from employees
      group by department_id) e2
join employees e1 on (e1.department_id = e2.department_id and e1.salary > e2."avg");

-- 6
-- max
select e1.employee_id, e1.last_name, e1.department_id, e1.salary
from employees e1
where salary > (select max(avg(salary))
                from employees
                group by department_id);
-- all
select e1.employee_id, e1.last_name, e1.department_id, e1.salary
from employees e1
where salary > all (select avg(salary)
                from employees
                group by department_id);

-- 7
select last_name, salary, department_id
from employees e
where employee_id in (
    with e4 as (select employee_id from (
        select employee_id
        from employees
        where department_id = 50  -- e.department_id  -- nu merge
        order by salary))
    select employee_id
    from e4
    where rownum <= 3);

-- 8
select department_name, last_name
from employees e
join departments d on e.department_id = d.department_id
where hire_date = (select min(hire_date) from employees where department_id = d.department_id)
order by 1;

-- 9
select last_name
from employees e1
where exists (
    select 1 from employees e2
    where e1.department_id = e2.department_id and salary = (
        select max(salary) from employees
        where department_id = 30)
    );

-- 10
select * from (
  select * from employees
  where salary = (select max(salary) from employees))
where rownum <= 3;

-- 11
select employee_id, last_name, first_name
from employees e
where exists (
    select 1 from employees
    where manager_id = e.employee_id
    having count(*) >= 2);    

-- 12
-- exists
select city
from locations l
where exists (
    select 1 from departments
    where location_id = l.location_id);
-- in
select city
from locations l
where location_id in (
    select location_id from departments);

-- 13
select department_name
from departments d
where not exists (
    select 1 from employees where department_id = d.department_id);

-- 14
-- a)
select employee_id, last_name, hire_date, salary, manager_id
from employees
where level = 2
start with last_name = 'De Haan'
connect by prior employee_id = manager_id;
-- b)
select employee_id, last_name, hire_date, salary, manager_id
from employees
where level > 1
start with last_name = 'De Haan'
connect by prior employee_id = manager_id;

-- 15
select employee_id, last_name, hire_date, salary, manager_id
from employees
start with employee_id = 114
connect by prior employee_id = manager_id;

-- 16
select employee_id, manager_id, last_name, level
from employees
where level >= 3  -- De Haan e pe nivelul 1
start with last_name = 'De Haan'
connect by prior employee_id = manager_id;

-- 17
select employee_id, manager_id, last_name, level
from employees e
start with employee_id = e.employee_id
connect by prior manager_id = employee_id;

-- 18
select employee_id, manager_id, last_name, salary, level
from employees
where salary > 5000
start with salary = (select max(salary) from employees)
connect by prior employee_id = manager_id;
                
-- 20
with subs as (
    select employees.*, level "lvl"
    from employees
    where level >= 2
    start with last_name = 'King'
    connect by prior employee_id = manager_id
    order by hire_date)
select employee_id, manager_id, last_name, first_name, job_id, hire_date, level
from subs
where to_char(hire_date, 'yyyy') != '1970'
start with "lvl" = 2
connect by prior employee_id = manager_id;    

-- 21 - not working !!!
select * from employees
where rownum <= 10
order by salary desc;

-- correct
select * from (
  select * from employees
  order by salary desc)
where rownum <= 10;

-- 22
select job_title, "joburi".*
from (
    select job_id, avg(salary) from employees
    group by job_id
    order by avg(salary)) "joburi"
join jobs j on(j.job_id = "joburi".job_id)
where rownum <= 3;
                
-- 23
select 'departamentul ' || department_name || ' este condus de ' ||  nvl(to_char(departments.manager_id),'nimeni') || ' si ' ||
case 
     when count(employee_id) = 0 then 'nu are angajati'
     else 'are numarul de angajati ' || count(employee_id)
end "informatii"
from employees right join departments using (department_id)
group by department_id, department_name, departments.manager_id;

-- 24
select last_name, first_name, nullif(length(last_name), length(first_name)) "lungime nume"
from employees
order by "lungime nume";

-- 25
-- case
select last_name, hire_date, salary,
case to_char(hire_date, 'yyyy')
when '1989' then salary * 1.20
when '1990' then salary * 1.15
when '1991' then salary * 1.10
else salary
end "Salariu dupa marire"
from employees;

-- decode
select last_name, hire_date, salary, decode(to_char(hire_date, 'yyyy'),
                                    '1989', (1 + 0.2) * salary,
                                    '1990', (1 + 0.15) * salary,
                                    '1991', (1 + 0.1) * salary,
                                    salary) "salariu_marit"
from employees;

-- alternativ
SELECT last_name, hire_date, salary,
    salary + DECODE(TO_CHAR(hire_date, 'YYYY'),
        1989, 20/100 * salary,
        1990, 15/100 *salary,
        1991, 10/100 * salary,
        0
    ) AS reised_salary
FROM employees;

-- 26
SELECT job_id,
(CASE 
when lower(job_id) LIKE 's%' then sum(salary)
when job_id= (SELECT job_id FROM employees WHERE salary =(SELECT max(salary) FROM employees)) then (SELECT AVG(salary) FROM employees)
ELSE min(salary)
END) rez 
FROM employees
GROUP BY job_id;


with suri as (select sum(salary) suma from employees where lower(job_id) like 's%')
select suma
from suri;