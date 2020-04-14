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
select count(distinct manager_id)
from employees;

-- 6
select max(salary) - min(salary) "Diferenta salarii"
from employees;

-- 7
select department_name, city, count(*) "Nr angajati", avg(salary)
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

-- 18
-- a)
select department_id, department_name, count(employee_id)
from departments
join employees using(department_id)
group by department_id, department_name
having count(employee_id) < 4;
-- b)
select department_id, department_name, count(employee_id)
from departments
join employees using(department_id)
group by department_id, department_name
having count(employee_id) = (select max(count(employee_id)) from employees group by department_id);

-- 19
select last_name, hire_date
from employees
where to_char(hire_date, 'dd') = (select to_char(hire_date, 'dd') from employees group by to_char(hire_date, 'dd')
                                  having count(to_char(hire_date, 'dd')) = (select max(count(employee_id)) from employees group by to_char(hire_date, 'dd')));

-- 20
select count(count(employee_id))
from employees
group by department_id
having count(employee_id) >= 15;

-- 21
select department_id, sum(salary)
from employees
where department_id != 30
group by department_id
having count(employee_id) > 10;

-- 22
select a.department_id, a.department_name, a.cnt, a.avg_salary, last_name, salary, job_id
from (select department_id, department_name, count(employee_id) cnt, round(avg(salary), 1) avg_salary
      from employees
      outer right join departments using(department_id)
      group by department_id, department_name) a
join employees e on(e.department_id = a.department_id);

-- 23
select city "Oras", department_id "Departmanet", job_id "Job", sum(salary) "Suma salarii"
from employees
join departments using(department_id)
join locations using(location_id)
where department_id > 80
group by department_id, city, job_id;

-- 24
select last_name, count(last_name) "Nr joburi"
from job_history jh
join employees using(employee_id)
group by last_name
having count(last_name) >= 2;

-- 25
select avg(coalesce(commission_pct, 0))
from employees;

-- 28
select
    (select count(employee_id) from employees) "Total",
    (select count(employee_id) from employees where to_char(hire_date, 'yyyy') = '1997') "1997",
    (select count(employee_id) from employees where to_char(hire_date, 'yyyy') = '1998') "1998",
    (select count(employee_id) from employees where to_char(hire_date, 'yyyy') = '1999') "1999",
    (select count(employee_id) from employees where to_char(hire_date, 'yyyy') = '2000') "2000"
from dual;

-- 30
select d.department_id, d.department_name, a.summ
from (
    select department_id, sum(salary) as summ
    from employees
    group by department_id
) a
inner join departments d on (a.department_id = d.department_id);

-- 31
select e.first_name, e.salary, e.department_id, a.mediu
from (
    select department_id, round(avg(salary)) as mediu
    from employees
    group by department_id
) a
inner join employees e  on (e.department_id = a.department_id);


-- 32
select e.first_name, e.salary, e.department_id, a.mediu, a.nr
from (
    select department_id, round(avg(salary)) as mediu, count(employee_id) as nr
    from employees
    group by department_id
) a
inner join employees e  on (e.department_id = a.department_id);

-- 33
select d.department_name, e.last_name, a.minim
from (select department_id, min(salary) as minim
      from employees
      group by department_id) a
inner join departments d on (d.department_id = a.department_id)
join employees e on (d.department_id = e.department_id and e.salary = a.minim);

-- 34
select a.department_id, a.department_name, a.cnt, a.avg_salary, last_name, salary, job_id
from (select department_id, department_name, count(employee_id) cnt, round(avg(salary), 1) avg_salary
      from employees
      outer right join departments using(department_id)
      group by department_id, department_name) a
join employees e on(e.department_id = a.department_id);