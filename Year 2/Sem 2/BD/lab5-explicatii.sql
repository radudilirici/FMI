-- 27
select job_id, 
  (select sum(salary) from employees where job_id = e.job_id and department_id = 30) Dept30,
  (select sum(salary) from employees where job_id = e.job_id and department_id = 50) Dept50,
  (select sum(salary) from employees where job_id = e.job_id and department_id = 80) Dept80,
  (select sum(salary) from employees where job_id = e.job_id) total
from employees e;

-- 28
SELECT 
  (SELECT COUNT(*)FROM employees) AS Total, 
  (SELECT COUNT(*) FROM employees e
     WHERE TO_CHAR(e.hire_date, 'yyyy') = '1997') AS Hired1997,
  (SELECT COUNT(*)
     FROM employees e
     WHERE TO_CHAR(e.hire_date, 'yyyy') = '1998') AS Hired1998,
  (SELECT COUNT(*)
     FROM employees e
     WHERE TO_CHAR(e.hire_date, 'yyyy') = '1999') AS Hired1999,
  (SELECT COUNT(*)
     FROM employees e
     WHERE TO_CHAR(e.hire_date, 'yyyy') = '2000') AS Hired2000
FROM dual;

select 5-2 from dual;

-- exemple subquery
select * from employees where hire_date > (select hire_date from employees where employee_id = 100);

select employee_id, a.dept_id, department_name from employees e
join 
  (select department_id dept_id, department_name from departments) a on (a.dept_id = e.department_id);
  
  
select * from (
  select employee_id, salary from employees
  where rownum = 1
  order by salary desc
);

select employee_id, e.salary, a.salary from (
 select department_id, avg(salary) salary from employees
 group by department_id
) a 
join employees e on (e.department_id = a.department_id)
where a.salary <= e.salary;

select employee_id, department_id, avg(salary) from employees e
join departments d using (department_id)
group by department_id, employee_id;

-- 30
SELECT d.department_id, d.department_name, a.summ
FROM (
    SELECT department_id, SUM(salary) AS summ
    FROM employees
    GROUP BY department_id
) a
INNER JOIN departments d on (a.department_id = d.department_id);

-- 31
SELECT e.first_name, e.salary, e.department_id, dep_summary.mediu
FROM (
    SELECT department_id, round(AVG(salary)) AS mediu
    FROM employees
    GROUP BY department_id
) dep_summary
INNER JOIN employees e on (e.department_id = dep_summary.department_id);

-- 32
SELECT e.first_name, e.salary, e.department_id, dep_summary.mediu, dep_summary.nr_ang
FROM (
    SELECT department_id, round(AVG(salary)) AS mediu, count(employee_id) as nr_ang
    FROM employees
    GROUP BY department_id
) dep_summary
INNER JOIN employees e on (e.department_id = dep_summary.department_id);

-- 33
select d.department_name, e.last_name, a.minim
from (select department_id, min(salary) as minim
      from employees
      group by department_id) a
inner join departments d on (d.department_id = a.department_id)
join employees e on (d.department_id = e.department_id and e.salary = a.minim);

SELECT a.department_id, a.department_name, e.last_name, e.salary
FROM (
    SELECT d.department_id, d.department_name, MIN(ee.salary) AS sal
    FROM departments d
    JOIN employees ee on (ee.department_id = d.department_id)
    GROUP BY d.department_name, d.department_id
) a
JOIN employees e on ( e.department_id = a.department_id)
WHERE e.salary = a.sal;

-- lab 5

-- ex 1.a
select department_name, job_title, round(avg(salary), 2) avg_salary from employees
join departments using (department_id)
join jobs using (job_id)
group by rollup (department_name, job_title);

-- echivalent (primul caz)
select avg_salary, department_name, job_title from (
select department_name, job_title, round(avg(salary), 2) avg_salary from employees
join departments using (department_id)
join jobs using (job_id)
group by department_name, job_title)
union all
-- echivalent (al doilea caz)
select avg_salary, department_name, null from (
select department_name, round(avg(salary), 2) avg_salary from employees
join departments using (department_id)
join jobs using (job_id)
group by department_name)
union all
-- echivalent (al treilea caz)
select avg_salary, null, null from (
select round(avg(salary), 2) avg_salary from employees
join departments using (department_id)
join jobs using (job_id)
);

-- 1.b
select department_name, job_title, round(avg(salary), 2) avg_salary, grouping(department_name), grouping(job_title) from employees
join departments using (department_id)
join jobs using (job_id)
group by rollup (department_name, job_title);
-- echivalent group by grouping sets ((department_name, job_title), (department_name), ())

-- ex 3
select department_name, job_title, e.manager_id, round(avg(salary), 2) avg_salary, grouping(department_name), grouping(job_title), grouping(e.manager_id)
from employees e
join departments using (department_id)
join jobs using (job_id)
group by grouping sets ((department_name, job_title), (job_title, e.manager_id), ());

-- exists example

select * from employees e
where exists (
  select 1 from departments d join locations l using (location_id)
  where d.department_id = e.department_id
  and lower(city) = 'oxford'
);

select * from employees 
where employee_id in (
  select employee_id from employees 
  join departments d using (department_id) 
  join locations l using (location_id)
  where lower(city) = 'oxford');
