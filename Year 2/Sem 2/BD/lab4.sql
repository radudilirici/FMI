-- 1
-- a) functiile grup ignora valorile null (cu exceptia lui COUNT(*))
-- b) in having putem pune functii precum sum(coloana). e folosit ca sa grupam sortarile

-- 2
select round(max(salary)) "Maxim", round(min(salary)) "Minim", round(sum(salary)) "Suma", round(avg(salary)) "Media"   
from employees;

-- 3
select job_id, round(max(salary)) "Maxim", round(min(salary)) "Minim", round(sum(salary)) "Suma", round(avg(salary)) "Media"   
from employees
group by job_id;

-- 4
select job_id, count(*) "Nr angajati"
from employees
group by job_id;

-- 5
select distinct manager_id
from employees
where manager_id is not null;

-- 6
select max(salary) - min(salary) "Diferenta salarii"
from employees;

-- 7
select department_name, city, count(*) "Nr angajati"
from departments d
join locations l on(l.location_id = d.location_id)
join employees e on(e.department_id = d.department_id)
group by d.department_name, l.city;

-- 8
select employee_id, last_name
from employees
where salary > (select avg(salary) from employees)
order by salary desc;

-- 9
select manager_id, min(salary) from employees
where manager_id is not null
group by manager_id
having min(salary) > 5000  -- ca sa se vada efectul
order by 2 desc;

-- 10
select department_id, department_name, max(salary)
from departments d
join employees e using(department_id)
group by department_id, department_name
having max(salary) > 8000;

-- 11
select avg(min(salary))
from employees
group by department_id;

-- 12
select department_id, department_name, sum(salary)
from employees
join departments using(department_id)
group by department_id, department_name;

-- 13
select max(avg(salary))
from employees
group by department_id;

-- 14
select job_id, job_title, avg(salary)
from employees
join jobs using(job_id)
group by job_id, job_title
having avg(salary) = (select min(avg(salary)) from employees group by job_id);

-- 15
select avg(salary)
from employees
having avg(salary) > 2500;

-- 16
select department_id, job_id, avg(salary)
from employees
join departments using(department_id)
join jobs using(job_id)
group by department_id, job_id
order by 1;

-- 17
select department_name, avg(salary)
from employees
join departments using(department_id)
group by department_name
having avg(salary) = (select max(avg(salary)) from employees group by department_id);