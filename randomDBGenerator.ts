// run with `deno --allow-net --allow-write randomDBGenerator.ts`
const res = await fetch('https://randomuser.me/api/?results=5000&nat=de');
const {results} = await res.json();

const nameData:string = results.map(({name }:{name: {last: string, first:string}}) => ([name.last, name.first, getRndInteger(0, 99999).toString().padStart(5, '0'), getRndInteger(10, 9999), getRndInteger(0,15)]).join(',')).join('\n\n');

Deno.writeTextFileSync('db.csv', nameData);

// min/max included
function getRndInteger(min:number, max:number) {
  return Math.floor(Math.random() * (max - min + 1) ) + min;
}
