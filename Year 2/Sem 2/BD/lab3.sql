-- Laborator 3

-- 1.1
select e.last_name, to_char(e.hire_date, 'Month yyyy')
from employees e
join employees s on (s.department_id = e.department_id and lower(s.last_name) = 'gates' and lower(e.last_name) like '%a%' and lower(e.last_name) != 'gates');
-- 1.2
select e.last_name, to_char(e.hire_date, 'Month yyyy')
from employees e, employees s
where s.department_id = e.department_id and lower(s.last_name) = 'gates' and instr(lower(e.last_name), 'a') > 0 and lower(e.last_name) != 'gates';
-- 2.1
select e.employee_id, e.last_name, d.department_id, d.department_name
from employees e
join departments d on (e.department_id = d.department_id)
where (select count(*)
       from employees s
       where lower(s.last_name) like '%t%' and s.department_id = e.department_id and s.employee_id != e.employee_id) > 0  -- nu stiam de distinct..
order by 2;
-- 2.2
select distinct e.employee_id, e.last_name, d.department_id, d.department_name
from employees e
join departments d on (e.department_id = d.department_id)
join employees s on (e.department_id = s.department_id and lower(s.last_name) like '%t%' and s.employee_id != e.employee_id)
order by 2;
-- 3
select e1.last_name, e1.salary, job_title, city, country_name
from employees e1
join jobs using(job_id)
join departments using(department_id)
join locations using(location_id)
join countries using(country_id)
join employees e2 on (e1.manager_id = e2.employee_id and e2.last_name = 'King');
-- 4
select department_id, department_name, last_name, job_id, to_char(salary, '$99,999.00')
from departments
join employees using(department_id)
where department_name like '%ti%'
order by department_name, last_name;
-- 5
select last_name, d.department_id, department_name, city
from employees e
join departments d on (d.department_id = e.department_id)
join locations l on (l.location_id = d.location_id and city = 'Oxford');
-- 6
select distinct e1.employee_id, e1.last_name, e1.department_id, e1.salary, (j.min_salary + j.max_salary) / 2 "avg"
from employees e1
join jobs j on (j.job_id = e1.job_id and e1.salary > (j.min_salary + j.max_salary) / 2)
join employees e3 on (e1.department_id = e3.department_id and lower(e3.last_name) like '%t%')
order by 3;
-- 7.1
select last_name, department_name
from employees
left outer join departments using(department_id);
-- 7.2
select last_name, department_name
from departments
right outer join employees using(department_id);
-- 8.1
select department_name, last_name
from employees
right outer join departments using(department_id);
-- 8.2
select department_name, last_name
from departments
left outer join employees using(department_id);
-- 9
select last_name, department_name
from employees
full outer join departments using(department_id)
order by 1;
--
select last_name, department_name
from employees
left outer join departments using(department_id)
union all  -- pentru ca duplicatele trebuie pastrate (numele e acelasi, dar prenumele nu)
select distinct last_name, department_name
from employees e
right outer join departments d on (e.department_id = d.department_id)
where last_name is null
order by 1;
-- 10
select department_id
from departments
where department_name like '%re%'
union
select department_id
from employees
where job_id = 'SA_REP';  -- rezultatele sunt ordonate dupa department_id
-- 11
select department_id
from departments
where department_name like '%re%'
union all
select department_id
from employees
where job_id = 'SA_REP'; -- avem duplicate din a doua cerere, iar union all le pastreaza. rezultatele nu mai sunt ordonate
-- 12
select department_id
from departments
minus
select department_id
from employees;
-- 13
select department_id
from departments
where department_name like '%re%'  -- nu exiatsta angajati in departamentele astea
intersect
select department_id
from employees
where job_id = 'HR_REP';
-- 14
select employee_id, job_id, last_name
from employees
where salary > 3000
union
select employee_id, job_id, last_name
from employees
natural join jobs
where salary = (min_salary + max_salary) / 2;
-- 15
select last_name, hire_date
from employees
where hire_date > (select hire_date from employees where last_name = 'Gates');
-- 16
select last_name, salary
from employees
where department_id = (select department_id from employees where last_name = 'Gates') and last_name != 'Gates';
-- 17
select last_name, salary
from employees
where manager_id = (select employee_id from employees where manager_id is null);
-- 18
select last_name, department_id, salary
from employees e1
where (department_id, salary) in (select department_id, salary from employees e2 where commission_pct is not null and e1.employee_id != e2.employee_id)
order by 2, 3;
-- 19
select distinct e1.employee_id, e1.last_name, e1.department_id, e1.salary, round(e2."avg", 2)
from employees e1
join (select department_id, avg(salary) "avg"
      from employees
      group by department_id) e2 
on (e1.department_id = e2.department_id and e1.salary > e2."avg")
join employees e3 on (e1.department_id = e3.department_id and lower(e3.last_name) like '%t%')
order by 3;
-- 20
select last_name
from employees
where salary > all (select salary from employees where job_id like '%CLERK%')  -- sau salary > slect max(salary) from ...
-- cu any trebuie ca salariul sa fie mai mare decat unul dintre functionari
order by salary desc;
-- 21
select last_name, department_name, salary, e1.manager_id
from employees e1
join departments using(department_id)
where commission_pct is null
and (select count(*) from employees e2 where e2.manager_id = e1.manager_id and e2.commission_pct is not null) > 0;
-- 22
select last_name, department_name, salary, job_title, commission_pct
from employees e1
join departments using(department_id)
join jobs j on (e1.job_id = j.job_id)
where (select count(*) from employees e2
       join departments d on(e2.department_id = d.department_id)
       join locations l on(d.location_id = l.location_id)
       where city = 'Oxford' and  e1.employee_id != e2.employee_id and e1.salary = e2.salary and e1.commission_pct = e2.commission_pct) > 0;
-- 23
select last_name, department_id, job_id
from employees
where department_id in (select department_id from departments
                       join locations using(location_id)
                       where city = 'Toronto');