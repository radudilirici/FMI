select * from turist;
select * from achizitioneaza;
select * from excursie;
-- Recapitulare
--ex1
select * from (select *
from achizitioneaza, excursie
order by 5 asc)
where rownum = 1;

--ex2
select cod_excursie, count(*)
from achizitioneaza
group by cod_excursie;

--ex3

select ag.denumire, ag.oras, count(*), avg(e.pret) from achizitioneaza ac
join excursie e on e.id_excursie = ac.cod_excursie
join agentie ag on ag.id_agentie = e.cod_agentie
group by ag.denumire, ag.oras;


--ex4 a)

select distinct tt.nume, tt.prenume from achizitioneaza ac
join excursie ee on ee.id_excursie = ac.cod_excursie
join turist tt on tt.id_turist = ac.cod_turist
where ee.id_excursie in (select a.cod_excursie from turist t
join achizitioneaza a on a.cod_turist = t. id_turist
group by a.cod_excursie
having count(*) >= 2);
--b)
select count(*) from 
(select distinct tt.nume, tt.prenume from achizitioneaza ac
join excursie ee on ee.id_excursie = ac.cod_excursie
join turist tt on tt.id_turist = ac.cod_turist
where ee.id_excursie in (select a.cod_excursie from turist t
join achizitioneaza a on a.cod_turist = t. id_turist
group by a.cod_excursie
having count(*) >= 2));

--ex5
select * from turist t
join achizitioneaza ac on ac.cod_turist = t.id_turist
join excursie e on e.id_excursie = ac.cod_excursie
where e.destinatie != 'Paris';

select * from agentie;
select * from achizitioneaza;
select * from excursie;
select * from turist;