package main

import (
	"fmt"
	"log"
)

// account
type account struct {
	name string
}

func newAccount(accountName string) *account {
	return &account{
		name: accountName,
	}
}

func (_account *account) checkAccount(accountName string) error {
	if _account.name != accountName {
		return fmt.Errorf("account name is incorrect")
	}
	fmt.Println("Account is verified")
	return nil
}

// security code
type securityCode struct {
	code int
}

func newSecurityCode(code int) *securityCode {
	return &securityCode{
		code: code,
	}
}

func (_securityCode *securityCode) checkCode(incomingCode int) error {
	if _securityCode.code != incomingCode {
		return fmt.Errorf("security code is incorrect")
	}
	fmt.Println("Security code is verified")
	return nil
}

// wallet
type wallet struct {
	balance int
}

func newWallet() *wallet {
	return &wallet{
		balance: 0,
	}
}

func (_wallet *wallet) creditBalance(amount int) {
	_wallet.balance += amount
	fmt.Println("Wallet balance is credited")
}

func (_wallet *wallet) debitBalance(amount int) error {
	if _wallet.balance < amount {
		return fmt.Errorf("wallet balance is not sufficent")
	}
	_wallet.balance -= amount
	fmt.Println("Wallet balance is debited")
	return nil
}

// ledger
type ledger struct{}

func (_ledger *ledger) makeEntry(accountID, txnType string, amount int) {
	fmt.Printf("Make ledger entry for accountId %s with txnType %s for amount %d\n", accountID, txnType, amount)
}

// notification
type notification struct{}

func (_notification *notification) notifyCredit() {
	fmt.Println("Notification for credit")
}

func (_notification *notification) notifyDebit() {
	fmt.Println("Notificatino for debit")
}

// Facade
type walletFacade struct {
	account      *account
	wallet       *wallet
	securityCode *securityCode
	notification *notification
	ledger       *ledger
}

func newWalletFacade(accountID string, code int) *walletFacade {
	return &walletFacade{
		account:      newAccount(accountID),
		wallet:       newWallet(),
		securityCode: newSecurityCode(code),
		notification: &notification{},
		ledger:       &ledger{},
	}
}

func (_walletFacade *walletFacade) validateAccount(accountID string, secCode int) error {
	err := _walletFacade.account.checkAccount(accountID)
	if err != nil {
		return err
	}
	err = _walletFacade.securityCode.checkCode(secCode)
	if err != nil {
		return err
	}
	return nil
}

func (_walletFacade *walletFacade) credit(accountID string, secCode int, amount int) error {
	err := _walletFacade.validateAccount(accountID, secCode)
	if err != nil {
		return err
	}

	_walletFacade.wallet.creditBalance(amount)
	_walletFacade.ledger.makeEntry(accountID, "Credit", amount)
	_walletFacade.notification.notifyCredit()
	return nil
}

func (_walletFacade *walletFacade) debit(accountID string, secCode int, amount int) error {
	err := _walletFacade.validateAccount(accountID, secCode)
	if err != nil {
		return err
	}

	err = _walletFacade.wallet.debitBalance(amount)
	if err != nil {
		return err
	}
	_walletFacade.ledger.makeEntry(accountID, "Debit", amount)
	_walletFacade.notification.notifyDebit()
	return nil
}

func app() {
	walletFacade := newWalletFacade("GOA.CASH", 1234)

	err := walletFacade.credit("GOA.CASH", 1234, 100)
	if err != nil {
		log.Fatalf("Error: %s\n", err.Error())
	}

	err = walletFacade.debit("GOA.CASH", 1234, 90)
	if err != nil {
		log.Fatalf("Error: %s\n", err.Error())
	}
}

func main() {
	app()
}
