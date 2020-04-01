select e1.employee_id, e1.last_name, e2.employee_id, e2.last_name
from employees e1, employees e2
where e1.manager_id = e2.employee_id(+);

select * from employees
natural join departments;

select d.department_id, e.employee_id from employees e
join departments d on (d.department_id <> e.department_id);

-- fara where face produs cartezian
select * from employees, departments;

select * from employees e, departments d
where e.department_id = d.department_id;

select * from employees e
left join departments d using (department_id);

select * from employees e
right join departments d using (department_id);

select * from departments;

select e1.employee_id, e1.manager_id, e1.department_id from employees e1
join employees e2 on (e1.manager_id = e2.employee_id)
join departments d on (e1.department_id = d.department_id)
join departments d2 on (d2.department_id = e2.department_id);

select * from employees
natural join departments
natural join locations;

select * from employees e1
right join employees e2 on (e1. manager_id = e2.employee_id);


select employee_id from employees
where department_id = 90
UNION
select employee_id from employees
where salary > 1000
order by 1;

select department_id from departments where department_name like '%r'
UNION
select department_id from employees where job_id = 'SA_REP';

select * from employees 
where employee_id in 
(select department_id from departments where department_name like '%re');

select * from employees
where hire_date > (select hire_date from employees where lower(last_name) = 'gates');