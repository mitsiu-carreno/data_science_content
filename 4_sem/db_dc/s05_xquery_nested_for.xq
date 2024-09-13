let $data :=
  <xml>
  <country name="Germany">
    <person age="34" name='John'/>
    <person age="30" name='Jack'/>
    <person age="30" name='Johann'/>
  </country>
  <country name='USA'>
    <person age="34" name='John'/>
    <person age="30" name='Jack'/>
    <person age="30" name='Johann'/>
  </country>
  </xml>
  
for $country in $data/country
  where $country/person/@name="John" and $country/person/@age=30
return $country

Germany + USA

for $country in $data/country
  for $person in $country/person
  where $person/@name="John" and $person/@age=30
return $country

<None>

for $country in $data/country
  for $person in $country/person
  where $person/@name="John" and $person/@age=34
return $country

USA + Germany
