var fs = require('fs');
var exec = require("child_process").exec;

var tests_in = [];
var tests_out = {};
var tests_ok = [];
var tests_er = [];

if(!process.argv[2] || !process.argv[3]){
    console.log("Usage: node test.js bin_file test_dir");
}

var bin = process.argv[2];
var test_dir = process.argv[3];

fs.readdirSync(test_dir).map(file=>{
    if(/^.*\.in$/.test(file))
        tests_in.push(file);
    else{
        var m = file.match(/^(.*)\.out$/);
        if(m!==null){
            tests_out[m[1]+".in"]=fs.readFileSync(test_dir+file).toString().replace("\n","");
        }
    }
});

function loop(n){
    test = tests_in[n];
    var output="";
    output+="\033[36m"
    output+=' '.repeat(15).substr(0,15-test.length);
    output+=test;
    output+='...';
    output+=' '.repeat(3);
    output+="\033[0m";
    process.stdout.write(output);

    exec(`${bin} < ${test_dir}/${test}`,(code,stdout,stderr)=>{
        var out = stdout.split("\n").slice(0,-1);
        var r = {
            name:test,
            time:out.length>=2?Number.parseFloat(out[0]):-1,
            passed:out.length>=2?out[1]===tests_out[test]:out[0]===tests_out[test]
        };
        if(r.passed)tests_ok.push(test);
        else        tests_er.push(test);
        var output="";
        output+=r.passed?"\033[32m":"\033[31m";
        output+=' '.repeat(3).substr(0,3-tests_out[test].length);
        output+=tests_out[test]+" ";
        output+=r.passed?"OK":"ERROR";
        output+=` [${r.time+'0'.repeat(8).substr(0,8-(r.time+"").length)}]`;
        output+="\033[0m\n";
        process.stdout.write(output);
        if(++n<tests_in.length)
            setTimeout(()=>loop(n),0);
        else{
            process.stdout.write("\033[36m");
            console.log("-".repeat(50));
            console.timeEnd("All tests");
            process.stdout.write("\033[32m");
            console.log(`OK: ${tests_ok.length}`);
            if(tests_er.length)process.stdout.write("\033[31m");
            console.log(`ERROR: ${tests_er.length}`);
            process.stdout.write("\033[36m");
            console.log("-".repeat(50));
            process.stdout.write("\033[0m");
        }
    })
};
console.time("All tests");
process.stdout.write("\033[36m");
console.log("-".repeat(50));
console.log(`Running ${tests_in.length} tests. КМБО-02-15: Kartavenko Denis`);
console.log("-".repeat(50));
process.stdout.write("\033[0m");
loop(0);
