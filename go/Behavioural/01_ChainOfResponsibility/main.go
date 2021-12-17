package main

import "fmt"

type patient struct {
	name           string
	registerStatus bool
	doctorStatus   bool
	medicineStatus bool
	paymentStatus  bool
}

type department interface {
	execute(*patient)
	setNext(department)
}

type reception struct {
	next department
}

func (_reception *reception) execute(_patient *patient) {
	if !_patient.registerStatus {
		_patient.registerStatus = true
	}
	fmt.Println("Reception start")
	_reception.next.execute(_patient)
	fmt.Println("Reception end")
}

func (_reception *reception) setNext(nextDept department) {
	_reception.next = nextDept
}

type doctor struct {
	next department
}

func (_doctor *doctor) execute(_patient *patient) {
	if !_patient.doctorStatus {
		_patient.doctorStatus = true
	}
	fmt.Println("Doctor start")
	_doctor.next.execute(_patient)
	fmt.Println("Doctor end")
}

func (_doctor *doctor) setNext(nextDept department) {
	_doctor.next = nextDept
}

type medical struct {
	next department
}

func (_medicine *medical) execute(_patient *patient) {
	if !_patient.medicineStatus {
		_patient.medicineStatus = true
	}
	fmt.Println("Medical start")
	_medicine.next.execute(_patient)
	fmt.Println("Medical end")
}

func (_medicine *medical) setNext(nextDept department) {
	_medicine.next = nextDept
}

type cashier struct {
	next department
}

func (_cashier *cashier) execute(_patient *patient) {
	if !_patient.paymentStatus {
		_patient.paymentStatus = true
	}
	fmt.Println("Cashier start")
	fmt.Println("Cashier end")
}

func (_cashier *cashier) setNext(nextDept department) {
	_cashier.next = nextDept
}

func app() {
	cashier := &cashier{}

	medical := &medical{}
	medical.setNext(cashier)

	doctor := &doctor{}
	doctor.setNext(medical)

	reception := &reception{}
	reception.setNext(doctor)

	patient := &patient{
		name: "Arun",
	}

	reception.execute(patient)
}

func main() {
	app()
}
