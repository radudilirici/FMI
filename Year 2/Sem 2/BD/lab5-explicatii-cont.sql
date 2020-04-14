select department_id, job_id, count(employee_id), grouping(department_id), grouping(job_id) from employees
join departments using (department_id)
group by rollup(department_id, job_id);

select department_id, job_id, count(employee_id), grouping(department_id), grouping(job_id) from employees
join departments using (department_id)
group by grouping sets((department_id, job_id), (department_id), ());

select department_id, job_id, count(employee_id), grouping(department_id), grouping(job_id) from employees
join departments using (department_id)
group by cube(department_id, job_id);

select department_id, job_id, count(employee_id), grouping(department_id), grouping(job_id) from employees
join departments using (department_id)
group by grouping sets((department_id, job_id), (department_id), (job_id), ());

select department_id, job_id, count(employee_id), grouping(department_id), grouping(job_id) from employees
join departments using (department_id)
group by grouping sets((job_id), (department_id));

select department_id, job_id, location_id, count(employee_id), grouping(department_id), grouping(job_id), grouping(location_id) from employees
join departments using (department_id)
group by grouping sets((department_id, location_id), (location_id, job_id), ());

-- ex 14
-- a)
select employee_id, last_name, hire_date, salary, manager_id
from employees 
where level <= 2
start with last_name = 'De Haan'
connect by prior employee_id = manager_id; 

-- b)
select employee_id, last_name, hire_date, salary, manager_id
from employees 
start with last_name = 'De Haan'
connect by prior employee_id = manager_id; 

-- ex 19
with deps as (
  select department_name, sum(salary) avg_sal
  from employees join departments using (department_id)
  group by department_name
)
select department_name, avg_sal from deps
where avg_sal > (select avg(sum(salary)) from employees group by department_id);

-- ex anii precedenti
with king as (
        select employee_id from employees
        where lower(first_name||last_name) = 'stevenking'),
    startpoints as (
        select employee_id from employees
        where hire_date = (
            select min(hire_date)
            from employees
            where manager_id = (
                select employee_id from king
            )
            and to_char(hire_date, 'YYYY') <> '1970'
        )
    )
select employee_id, last_name || ', ' || first_name, job_id, manager_id, hire_date
from employees
start with employee_id = (
    select employee_id from startpoints
)
connect by manager_id = prior employee_id;

-- 21 - not working !!!
select * from employees
where rownum <= 10
order by salary desc;

-- correct
select * from (
  select * from employees
  order by salary desc
)
where rownum <= 10;


-- 24
select last_name, first_name, nullif(length(last_name), length(first_name)) "lungime nume"
from employees
order by "lungime nume";

-- 23
select 'departamentul ' || department_name || ' este condus de ' || departments.manager_id ||
  nvl(to_char(departments.manager_id),'nimeni') || ' si ' || 
case 
     when count(employee_id) = 0 then 'nu are angajati'
     else 'are numarul de angajati ' || count(employee_id)
end "informatii"
from employees right join departments using (department_id)
group by department_id, department_name, departments.manager_id;

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
