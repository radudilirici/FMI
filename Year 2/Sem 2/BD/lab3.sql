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
join employees e2 on(e1.manager_id = e2.employee_id and e2.last_name = 'King');
-- 4
select department_id, department_name, last_name, job_id, to_char(salary, '$99,999.00')
from departments
join employees using(department_id)
where department_name like '%ti%'
order by department_name, last_name;
-- 5
select last_name, d.department_id, department_name, city
from employees e
join departments d on(d.department_id = e.department_id)
join locations l on(l.location_id = d.location_id and city = 'Oxford');
-- 6.1  am citit Obs. dupa ce am rezolvat :D
select distinct e1.employee_id, e1.last_name, e1.department_id, e1.salary, e2."avg"
from employees e1
join (select department_id, avg(salary) "avg"
      from employees
      group by department_id) e2 
on(e1.department_id = e2.department_id and e1.salary >= e2."avg")
join employees e3 on (e1.department_id = e3.department_id and lower(e3.last_name) like '%t%')
order by 3;
-- 6.2
select distinct e1.employee_id, e1.last_name, e1.department_id, e1.salary, (j.min_salary + j.max_salary) / 2 "avg"
from employees e1
join jobs j on (j.job_id = e1.job_id and e1.salary >= (j.min_salary + j.max_salary) / 2)
join employees e3 on (e1.department_id = e3.department_id and lower(e3.last_name) like '%t%')
order by 3;
-- 7
