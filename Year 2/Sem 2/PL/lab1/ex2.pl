%---------------------------------
% Jon Snow and Daenerys Targaryen
%---------------------------------

male(rickardStark).
male(eddardStark).
male(brandonStark).
male(benjenStark).
male(robbStark).
male(aerysTargaryen).
male(rhaegarTargaryen).


%---------------------------

female(lyarraStark).
female(catelynStark).
female(lyannaStark).
female(sansaStark).
female(aryaStark).
female(rhaellaTargaryen).
female(eliaTargaryen).

%------------------------

parent_of(rickardStark, eddardStark)
parent_of(lyarraStark, eddardStark)


%------------------------

father_of(Father, Child) :- parent_of(Father, Child), male(Father)
mother_of(Mother, Child) :- parent_of(Mother, Child), female(Mother)
grandfather_of(Grandfather, Child) :- parent_of(Grandfather, Father), parent_of(Father, Child)
