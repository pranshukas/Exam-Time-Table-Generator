const form = document.getElementById("form");
const input = document.getElementById("input");
const data = document.querySelector(".data");

// Taking input from the form

form.addEventListener("submit", (e) => {
    e.preventDefault();
    if (+input.value >= 4) {
        input.value = "";
        alert("Currently Not Supporting More than 3 Semesters");
    } else if (+input.value <= 0) {
        input.value = "";
        alert("Please Enter Valid Input");
    } else {
        data.style.display = "none";
        createSemesters(input.value);
    }
});

function createSemesters(numberofSemesters) {
    // Displaying Semesters
    const createSemesters = document.querySelector(".create-semesters");
    createSemesters.style.display = "flex";

    // Creating Cards for Semesters

    for (let idx = 1; idx <= 2 * numberofSemesters; idx += 2) {
        const divEl = document.createElement("div");
        divEl.classList.add("semester");
        divEl.classList.add("semester" + idx);
        divEl.innerHTML = `
        <h1>Enter Subject Codes for Semester ${idx} (inlcuding Any Overload of Previous Semesters)</h1>
            <button class="btn btn-add">+</button>
            <button class="btn btn-sub">-</button>
            <div class="card"></div>
        `;
        createSemesters.append(divEl);
    }

    // Displaying Generate Button and Adding Event Listeners to it

    const generateBtn = document.getElementById("generate-btn");
    generateBtn.style.display = "block";
    generateBtn.addEventListener("click", generate);

    // Adding Event Listeners to + and - buttons

    const addButtons = document.querySelectorAll(".btn-add");
    addButtons.forEach((button) => {
        button.addEventListener("click", () => {
            // console.log(button.parentNode.querySelector(".card"));
            const card = button.parentNode.querySelector(".card");
            const inp = document.createElement("input");
            card.appendChild(inp);
        });
    });

    const subButtons = document.querySelectorAll(".btn-sub");
    subButtons.forEach((button) => {
        button.addEventListener("click", () => {
            // console.log(button.parentNode.querySelector(".card"));
            const card = button.parentNode.querySelector(".card");
            card.removeChild(card.lastChild);
        });
    });
}

var subjectCodes = [];

function generate() {
    const createSemesters = document.querySelector(".create-semesters");
    const generateBtn = document.getElementById("generate-btn");
    // createSemesters.style.display = "none";
    // generateBtn.style.display = "none";

    const semesterData = createSemesters.querySelectorAll(".semester");
    semesterData.forEach((semester) => {
        const subjects = semester.querySelector(".card").querySelectorAll("input");
        // console.log(subjects);
        var semSubjectCode = [];

        subjects.forEach((subject) => {
            // console.log(subject.value);
            semSubjectCode.push(subject.value);
        });

        subjectCodes.push(semSubjectCode);
    });

    console.log(subjectCodes);

    // Initialize Graph 
    let adj = { };
    for(var idx=0; idx<subjectCodes.length; idx++) {
        var subject = subjectCodes[idx];

        for(var i=0; i<subject.length; i++) {
            adj[subject[i]] = new Array();
            for(var j=0; j<subject.length; j++) {
                if(i!=j) {
                    adj[subject[i]].push(subject[j]);
                }
            }
        }
    }   
    // Initializing Color of Each Node to be -1
    let color = new Map();
    for(var i in adj) {
        color[i]=-1;
    }
    color[adj[0].key];
    console.log(adj);
    console.log(color);
}
