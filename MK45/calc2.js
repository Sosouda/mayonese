let disp = '';
let realA = '';
let realB = '';
let memA = '';
let memB = '';
let flotA = false;
let flotB = false;
let flotn = false;

let sign = '';
let memorysign = false;

let mem = '';
let expOrder = '';
let lastOperation = null;
let lastOperand = null;
let stack = [];

let expMode = false;
let expV = false;
let finish = false;
let radian = false;
let arc = false;
let overflow = false;

const digit = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'];
const twoOperands =['-', '+', '✕', '÷', 'yˣ'];
const oneOperand = ['1/x', 'ln', 'lg', '√', '10ˣ', 'n!', 'eˣ'];
const memOperands =['П÷','П✕','П-','П+','x<->п', 'п->x', 'x->п','СП']; 
const angleOperands =['sin', 'cos', 'tg','Р->Г','Г->Р']

let max = Math.pow(10,99) * 9;
let min = Math.pow(10,99) * 1;

const out = document.querySelector('.calc-screen .main-output');
const porOut = document.querySelector('.calc-screen .additional-output'); // Дополнительный экран
const signOut = document.querySelector('.calc-screen .sign-output');

function clear(){
    if(overflow){
        disp = '';
        realA = 0;
        expOrder = '';
        if(realB !== '') flotA = false;
        else flotB = false;
        flotn = false;
        signOut.textContent = '';
        porOut.textContent = '';
        out.textContent = '0';
        overflow = false;
        arc =false;
        memorysign = false;
        return;
    }
    else if(disp !== ''){
        disp = '';
        realA = 0;
        expOrder = '';
        if(realB !== '') flotA = false;
        else flotB = false;
        flotn = false;
        memorysign = false;
        signOut.textContent = '';
        porOut.textContent = '';
        out.textContent = '0';
       return;
    }
    
    disp = '';
    realA = '';
    realB = '';
    flotA = false;
        flotB = false;
        flotn = false;
        
        sign = '';
        memorysign = false;
        
        expOrder = '';
        lastOperation = null;
        lastOperand = null;
        stack = [];
        
        expMode = false;
        expV = false;
        finish = false;
        arc = false;
        overflow = false;
        signOut.textContent = '';
        porOut.textContent = '';
        out.textContent = '0';
    console.log(disp,realA,realB,sign,finish,expOrder,expMode)
}

function Degrees(rad){ 
    console.log(disp);
    return rad * (Math.PI/ 180);
}


function updateDisplay(value) {
    
    if(value === 0){
        if(signOut.textContent === '-') signOut.textContent = '-';
        else signOut.textContent = '';
        out.textContent = value;
    }

    else if(value < 0){
        signOut.textContent = '-';
        value  = value.toString().slice(1);
        out.textContent = value;
    }
    else{
         signOut.textContent = ' ';
         out.textContent = value;
    }
    
}

function OverFlowing(){
    out.textContent = ". . . . . . . .";
    signOut.textContent = '';
    porOut.textContent = '';
}

function updateAdditionalOutput(value) {
    porOut.textContent = value;
    if(disp.toString().length !== 0){
        if(signOut.textContent == '-'){
            out.textContent = 0;
            signOut.textContent = '-';
        }
        else{
            updateDisplay(disp);
        }
    } 
    else{
        out.textContent = 0;
        if(signOut.textContent === " ") {
            signOut.textContent = '';   
        }
        else if(signOut.textContent === '-'){
            signOut.textContent = '-';
        }
    }

}

function GradRad() {
    radian = !radian; 
}

document.getElementById('toggleSwitch').addEventListener('change', function() {
    GradRad(); 
});

document.querySelector('.C').onclick = clear

document.querySelector('.buttons').onclick = (event) => {
    if(!event.target.classList.contains('btn')) return;
    if(event.target.classList.contains('C')) return;
    
   
    out.textContent= '' ;
    const key = event.target.textContent;

    if(key === 'arc'){
        arc = true;
        if(disp === '') out.textContent = 0;
        else updateDisplay(disp);
    }

    if(key === '/-/'){
        if(!expV){
            if(disp === ''  || disp === 0){ 
                if(signOut.textContent === " "){
                    signOut.textContent = '-';
                    if(out.textContent !== ''){
                        out.textContent = disp;
                    }
                    else out.textContent = 0;
                }
                else{
                    signOut.textContent = ' ';
                    if(out.textContent !== ''){
                        out.textContent = disp;
                    }
                    else out.textContent = 0;
                }
                return;
            }
            
            
            if (disp[0] === '-') {
                disp = disp.slice(1);
                realA *= -1; 
            } 
            else 
            {
                disp = '-' + disp;
                realA *= -1; 
            }
            updateDisplay(disp);  
        }
        else{
            if(expOrder !== ''){
                if (expOrder[0] === '-') {
                    expOrder = expOrder.slice(1); 
                } else {
                    expOrder = '-' + expOrder; 
                }
                updateAdditionalOutput(expOrder);
            }
            else updateAdditionalOutput(0);
        }
    }
    
    if (key === '[(') {
        stack.push({ realA, realB, sign, finish });
        memB = realA;
        
        realB = ''; 
        sign = ''; 
        finish = false;
        console.log(stack);
        if(disp === '') out.textContent = 0;
        else updateDisplay(disp);
        disp = ''; 
        realA = disp;
    }  else if (key === ')]') {
        if (realB !== '') {
            executeLastOperation();  
        }
        realB = memB;
        const innerResult = disp;
        realA = disp; 

        if(stack.length !== 0){
            const { realA: prevA, realB: prevB, sign: prevSign } = stack.pop();
            if (prevSign) {  
                realB = prevA;
                disp = realB;
                sign = prevSign;
                realA = innerResult;
                executeLastOperation();
            } else {
                realA = innerResult;
                disp  = realA;
            }
            memB = realA;
            if(disp !== '')updateDisplay(disp);
            else out.textContent = 0;
        }
        else{
            overflow = true;
            OverFlowing();
        }
        
    }

    if(digit.includes(key)){
        if(overflow) {
            OverFlowing();
            return;
        }
            if(!expV){
                if(sign === ''){
                    if(key === '.' && (disp === '' || disp === '0')){
                        disp = '0.';
                        flotB = true;
                        realA = 0;
                        out.textContent = disp;
                        updateDisplay(disp);
                        return;
                    }
                    else if(key === '.'){
                        if(flotB === false) disp+='.';
                        flotB = true;
                        realA = disp;
                        out.textContent = disp;
                        updateDisplay(disp);
                        return;
                    }
                    else{
                        if(disp.toString().length <= 8 && flotB){ 
                            if(memorysign !== false){
                                disp =key;
                                if(expOrder !== '')expOrder = '';
                                memorysign = false;
                                }
                                else disp += key
                            realA = disp;
                            updateAdditionalOutput(expOrder);
                            updateDisplay(disp);
                            return;
                        }
                        else if(disp.toString().length <= 7){
                            if(key === '0' && (disp === '' || disp === '0' || disp === 0)){
                                if(signOut.textContent ==='-'){
                                    out.textContent = 0;
                                    signOut.textContent = '-';

                                }
                                else{
                                    out.textContent = 0;
                                    signOut.textContent = '';
                                }
                                return;
                            }
                            if(memorysign !== false){
                            disp =key;
                            if(expOrder !== '')expOrder = '';
                            memorysign = false;
                            }
                            else disp += key
                        }
                        else if(memorysign !== false){
                            disp =key;
                            if(expOrder !== '')expOrder = '';
                            memorysign = false;
                            }
                        if(disp.toString().length === 1 &&  signOut.textContent === '-') disp = disp * -1;
                        realA = disp;
                        updateAdditionalOutput(expOrder);
                        updateDisplay(disp);
                    }
                }
                else if(realA !== ''  && realB === '' && finish){
                    realB = memA * Math.pow(10,expOrder);
                    console.log(realB, "<-b");
                    expOrder = '';
                    disp = '';
                    if(key === '.' && (disp === '' || disp === '0')){
                        disp = '0.';
                        flotA = true;
                        realA = 0;
                        out.textContent = disp;
                        updateDisplay(disp);
                        return;
                    } 
                    else if(key === '.'){
                        if(flotA === false) disp= disp + '.';
                        flotA = true;
                        realA = disp;
                        out.textContent = disp;
                        updateDisplay(disp);
                        return;
                    }
                    realA = key;
                    disp = realA;
                    finish = false;
                    updateDisplay(disp);
                    updateAdditionalOutput(expOrder);
                    return;
                }
                else if(sign !== ''){
                    if(realB === ''){
                        realB = realA * Math.pow(10,expOrder);
                        console.log(realB);
                        expOrder = '';
                        if(expOrder !== 0)updateAdditionalOutput(expOrder);
                        else updateAdditionalOutput('');
                        disp = '';
                        realA = disp;
                    }
                    signOut.textContent = ' ';
                    if(key === '.' && (disp === '' || disp === '0')){
                        disp = '0.';
                        flotA = true;
                        realA = 0;
                        out.textContent = disp;
                        updateDisplay(disp);
                        return;
                    } 
                    else if(key === '.'){
                        if(flotA === false) disp= disp + '.';
                        flotA = true;
                        realA = disp;
                        out.textContent = disp;
                        updateDisplay(disp);
                        return;
                    }
                    else{
                        if(disp.toString().length <= 8 && flotA){ 
                            if(memorysign !== false){
                                disp =key;
                                if(expOrder !== '')expOrder = '';
                                memorysign = false;
                                }
                                else disp += key
                            realA = disp;
                            updateAdditionalOutput(expOrder);
                            updateDisplay(disp);
                            return;
                        }
                        if(disp.toString().length <= 7){
                            if(key === '0' && disp === ''){
                                if(signOut.textContent ==='-'){
                                    disp = 0;
                                    out.textContent = 0;
                                    signOut.textContent = '-';

                                }
                                else{
                                    disp = 0;
                                    out.textContent = 0;
                                    signOut.textContent = '';
                                }
                                return;
                            }
                            else if(disp === 0 || disp === "0"){
                                 disp = key;
                                 realA = disp;
                                 updateDisplay(disp);
                                 return;
                                }
                            else if(memorysign !== false){
                                    disp =key;
                                    if(expOrder !== '')expOrder = '';
                                    memorysign = false;
                                    }
                            else disp += key
                        } 
                        else if(memorysign !== false){
                            disp =key;
                            if(expOrder !== '')expOrder = '';
                            memorysign = false;
                            }
                        if(disp.toString().length === 1 &&  signOut.textContent === '-') disp = disp * -1;
                        realA = disp;
                        updateAdditionalOutput(expOrder);
                        updateDisplay(disp);
                        
                    }

                }
            }
            else{
                if(expOrder[0] === '-'){
                if(expOrder.length < 3) if(expOrder[0] === 0 || expOrder === '0'){
                    if(key !== '0'){
                    expOrder += (+key);
                    }
                    else expOrder = key;
                }
                else expOrder += (+key);
                else{ 
                    let tempEO = expOrder;
                    expOrder = expOrder.slice(3);
                    expOrder += '-';
                    expOrder += tempEO[2];
                    expOrder += (+key);
                        
                    }
                    
                }
                else{
                    if(expOrder.length < 2) {
                        if(expOrder[0] === 0 || expOrder === '0'){
                            if(key !== '0'){
                            expOrder += (+key);
                            }
                            else expOrder = key;
                        }
                        else expOrder += (+key);
                    }
                    else{
                    expOrder = expOrder.slice(1);
                    expOrder += (+key);
                    }
                }
                updateAdditionalOutput(expOrder);
                
            }
    }
    else if(key == 'π' && !expV){
        if(overflow) {
            OverFlowing();
            return;
        }
        if(realA === '')realA = 3.1415926;
        else{
            realB = realA;
            realA = 3.1415926;   
        }
        disp = realA;
        if(realB === '') flotB = true;
        else flotA = true;
        updateDisplay(disp);
        console.log(disp,sign);
    }
    



    function executeLastOperation() {
        if(overflow) {
            OverFlowing();
            return;
        }
                if (sign && realB !== '') {
                    realA = realA * Math.pow(10, expOrder);
                    switch(sign){
                        case '+':
                            realA = (+realB) + (+realA);
                            break;
                        case '-':
                            console.log(realA ,realB, memA);
                            if(realB !== memA) realA = realB - realA;
                            else realA = realA - memA;
                            break;
                        case '✕':
                            realA = realB * realA;
                            break;
                        case '÷':
                            if(realA === '' || realA === 0){
                                out.textContent = ". . . . . . . .";
                                porOut.textContent = '';
                                disp = 0;
                                realA = disp;
                                return;
                            }
                            if(realB !== memA) realA = realB / realA;
                            else realA = realA / memA;
                            break;
                        case 'yˣ':
                            if(realA < -100 || realA > 100 || realB < 0){
                                overflow = true;
                                OverFlowing();
                                realA = 0;
                                return;
                            }
                            realA = Math.pow(realB,realA);
                            break;
                        case '':
                            break;  
                    
                    }
                    lastOperation = sign;
                    lastOperand = memA;
                    realB ='';  
                }
                else if(sign && realB === ''){
                    
                    lastOperation = sign;
                    realB =  memA;
                    lastOperand = memA;
                }
                let aStr = realA.toString();
                if((aStr.includes('9999999999') || aStr.includes('000000001') || aStr.includes('000000002'))){
                    if(realA.toFixed(7) !== 0) realA = realA.toFixed(7);
                }
                expOrder = '';
                update1();
                return;
    }

    if (twoOperands.includes(key)) {
        memA = realA;
        if(expV) expV = false;
        sign = key;
        if(sign !== lastOperation && finish){
            realB = '';
            if(disp !== '')updateDisplay(disp);
             else out.textContent = 0;
            return;
        }
        if(realB !== '')executeLastOperation(); 
        else{
             if(disp !== '')updateDisplay(disp);
             else out.textContent = 0;
        }

        return;
    }


    if(oneOperand.includes(key)){
        if(overflow){
            OverFlowing();
            return;
        }
        memorysign = true;
        let signOo = key;
        if(realA === '') realA = 0;
        realA = realA * Math.pow(10,expOrder);
        switch(signOo){
            case 'eˣ':
                if(realA < -100 || realA > 100){
                    overflow = true;
                    OverFlowing();
                    return;
                }
                realA = Math.pow(2.7182818, realA);
                break;
            case '1/x':
                if(realA === '' || realA === '0' || realA === 0){ 
                    overflow = true;
                    OverFlowing();
                    return;
                }
                realA = 1 / realA;
                break;
            case 'ln':
                if(realA === '' || realA === '0' || realA <=0){ 
                    overflow = true;
                    OverFlowing();
                    return;
                }
                realA = Math.log(realA);
                break;
            case 'lg':
                if(realA === '' || realA === '0' || realA <= 0){ 
                    overflow = true;
                    OverFlowing();
                    return;
                }
                realA = Math.log10(realA);
                break;
            case '√':
                if(realA < 0){
                    overflow = true;
                    OverFlowing();
                    return;
                }
                realA = Math.sqrt(realA);
                break;
            case '10ˣ':
                if(realA < -99 || realA >= 100){
                    overflow = true;
                    OverFlowing();
                    return;
                }
                if(realA > 20){
                    expOrder = parseInt(realA);
                    realA = 1;
                    disp = realA;
                    updateDisplay(disp);
                    updateAdditionalOutput(expOrder);
                    return;
                }
                realA = Math.pow(10,realA);
                break;
            case 'n!':
                function factorial(n) {
                    if (n === 0 || n === 1) return 1;
                    else if( n < 0){
                        overflow = true;
                        OverFlowing();
                    }
                    return  n * factorial(n - 1);
                }

                if(realA <= 170 && !flotn) realA = factorial(realA);
                else  {
                    overflow = true;
                    OverFlowing();
                    return;
                }
                
                break;
            case '':
                break;
        }
        if(key !== '10ˣ' && key !== 'n!' && realA !== 0){
            if(realB !== '') flotA = true;
            else flotB = true;
            console.log(realA);
            expOrder = '';
            console.log(realA);

        }
        update1();
        
    }


    if(memOperands.includes(key)){
        if(overflow) {
            OverFlowing();
            return;
        }
        if(realA === '')realA = 0;
        realA = realA * Math.pow(10,expOrder);
        let signm = key;
        switch (signm) {
            case 'П+':
                mem = mem + realA;
                break;
            case 'П-':
                mem = mem - realA;
                break;
            case 'П✕':
                mem = mem * realA;
                break;
            case 'П÷':
                if (disp === '' || disp === '0' || disp === 0) {
                   overflow = true;
                   OverFlowing();
                   return;
                }
                mem = mem / realA;
                break;
            case 'x<->п':
                expOrder = '';
                let temp = realA;
                if(mem == '' || mem == 0 || mem == '0'){
                    realA = '';
                    
                } else realA = mem;
                mem = temp;
                break;
            case 'x->п':
                mem = realA;
                break;
            case 'п->x':
                expOrder = '';
                if(mem !== 0) realA = mem  ;
                else {
                    out.textContent = 0;
                    porOut.textContent = '';
                    signOut.textContent = '';
                    realA = 0;
                    return;
                }
                break;
            case 'СП':
                mem = 0;
                break;
        }
        memorysign = true;
        update1();
    }

    if(angleOperands.includes(key)){
        if(overflow){
            OverFlowing()
            return;
        }
        memorysign = true;
        if(realA === '')realA = 0;
        realA = realA * Math.pow(10,expOrder);
        let signa = key;
        switch(signa){
            case 'Р->Г':
                realA = (realA * 180)/Math.PI;
                if (String(realA).includes('.99')) {
                    realA = Math.round(realA);
                }
                break;
            case 'Г->Р':
                realA =  Degrees(realA);
                break;
            case 'sin':
                if(arc){
                    if (realA < -1 || realA > 1) {
                        overflow = true;
                        OverFlowing();
                        return;
                    }
                    if (radian) {
                        realA = Math.asin(realA);
                    } else {
                        realA = Math.asin(Degrees(realA));
                    }
                }
                else{
                    if (radian) {
                    realA = Math.sin(realA);
                    } else {
                        realA = Math.sin(Degrees(realA));
                    }
                }
            break;           
            case 'cos':
                if(arc){
                    if (realA < -1 || realA > 1) {
                        overflow = true;
                        OverFlowing();
                        return;
                    }
                    if (radian) {
                        realA = Math.acos(realA);

                    } else {
                        realA = Math.acos(Degrees(realA));
                    }
                }
                else{
                    if (radian) {
                        realA = Math.cos(realA);

                    } else {
                        realA = Math.cos(Degrees(realA));
                    }
                }
            break;
            case 'tg':
                if(arc){
                    if (realA < -1 || realA > 1) {
                        overflow = true;
                        OverFlowing();
                        return;
                    }
                    if (radian) {
                        realA = Math.atan(realA);
                    } else {
                        realA = Math.atan(Degrees(realA));
                    }
                }
                else{
                    if (radian) {
                        realA = Math.tan(realA);
                    } else {
                        if (realA % 180 === 90) { 
                            overflow=true;
                            OverFlowing();
                            return;
                        }
                        realA = Math.tan(Degrees(realA));
                    }
                }
            break;
        }
        let aStr = realA.toString();
        if(aStr.includes('e') === true){
            const exponentialForm = aStr.split('e');
                expOrder = parseInt(exponentialForm[1]);
            if(expOrder < -10) {
                realA = 0;
                expOrder = '';
            }
        }
        if(aStr.includes('9999') || aStr.includes('0000')){
            realA = Math.round(realA*2)/2;
        }
        realA = parseFloat(realA.toString().slice(0, 9));
        expOrder = '';
        update1();
    }

    if(key === 'ВП'){
        if(overflow) {
            OverFlowing();
            return;
        }
        expMode = true;
        expV = !expV;
        if(expOrder === '' || expOrder === '0') updateAdditionalOutput(0);
        else updateAdditionalOutput(expOrder);
        console.log(expMode, expV, expOrder);
    }

    if (key === '=') {
        if (lastOperation && lastOperand !== null && realB === '') {
            realB = memA;
            executeLastOperation();
        }
        else {
            memA = realA;
            executeLastOperation();
        }
        finish = true;
    }
    
    function update1(){
        if(flotA || flotB) flotn = true;
        let aStr = Math.abs(realA).toString();
        if(aStr.length > 9 && flotn){
            expMode = true;
            aStr = Number(realA).toExponential();
            console.log(aStr);
            const exponentialForm = aStr.split('e');
                realA = parseFloat(exponentialForm[0]); 
                expOrder = parseInt(exponentialForm[1]);
            if(realA.toString().length > 9) realA = parseFloat(realA.toString().slice(0, 9));

            if(expOrder > 99 || expOrder < -99){
                overflow = true;
                OverFlowing();
                return;
            }
        }
        else if(aStr.length === 9 && flotn){
            if(realA.toString().includes('.') === false){
                if(flotA) flotA =false;
                if(flotB) flotB = false;
                flotn = false;
            }
        }
        else if(aStr.length > 8 && !flotn){
            expMode = true;
            let aStr = Number(realA).toExponential();
            console.log(aStr);
            const exponentialForm = aStr.split('e');
                realA = parseFloat(exponentialForm[0]); 
                expOrder = parseInt(exponentialForm[1]);
            if(realA.toString().length > 8) realA = parseFloat(realA.toString().slice(0, 7));

            if(expOrder > 99 || expOrder < -99){
                overflow = true;
                OverFlowing();
                return;
            }
        }
        else if(aStr.includes('e')){
            const exponentialForm = aStr.split('e');
                expOrder = parseInt(exponentialForm[1]);
            if(expOrder >=-7 && expOrder <= -1){
                realA = realA.toFixed(7);
                expOrder = '';
            }
            else realA = parseFloat(exponentialForm[0]); 
        }
        if(expOrder > 99 || expOrder < -99){
            overflow = true;
            OverFlowing();
            return;
        }
        disp = realA;
        if (expOrder!== 0)updateAdditionalOutput(expOrder);
        else updateAdditionalOutput('');
        if(disp !== '')updateDisplay(disp);
        else updateDisplay(0);
    }
}