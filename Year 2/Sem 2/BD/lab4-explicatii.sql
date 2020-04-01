select department_id, job_id, count(employee_id), min(salary), max(salary) from employees
group by department_id, job_id;

select count(*) from employees;
select count(department_id) from employees;

select job_id, sum(salary) from employees
where lower(last_name) not like '%t%'
group by job_id;

-- having filtreaza gruparile
select job_id, sum(salary) from employees
group by job_id
having sum(salary) > 10000;

-- where nu suporta group func, si filtreaza doar linii
select job_id, sum(salary) from employees
where salary > 10000
group by job_id;


select employee_id, last_name from employees
where salary > (select avg(salary) from employees);

-- rollup
SELECT department_id, TO_CHAR(hire_date, 'yyyy'), job_id, SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY ROLLUP(department_id, TO_CHAR(hire_date, 'yyyy'), job_id);

select department_id, TO_CHAR(hire_date, 'yyyy'), SUM(salary)
FROM employees
WHERE department_id < 50
group by department_id, TO_CHAR(hire_date, 'yyyy');

select department_id, sum(salary)
FROM employees
WHERE department_id < 50
group by department_id;

select sum(salary)
FROM employees
WHERE department_id < 50;

-- cube
SELECT department_id, TO_CHAR(hire_date, 'yyyy'), SUM(salary)
FROM employees
WHERE department_id < 50
GROUP BY cube(department_id, TO_CHAR(hire_date, 'yyyy'));

-- ex3
select job_id, min(salary), max(salary), avg(salary), sum(salary) from employees
group by job_id;

-- ex9
select manager_id, min(salary), max(salary) from employees
where manager_id is not null
group by manager_id
having min(salary) > 5000
order by 2 desc;
 
