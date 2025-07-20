/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarmitan <aarmitan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 17:34:02 by aarmitan          #+#    #+#             */
/*   Updated: 2025/07/20 14:28:50 by aarmitan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <ctime>
#include <stdio.h>
#include <time.h>
#include <cstring>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

Account::Account(int initial_deposit) {

  this->_nbDeposits = 0;
  this->_nbWithdrawals = 0;
  this->_amount = initial_deposit;
  this->_accountIndex = Account::_nbAccounts;
  Account::_nbAccounts++;
  Account::_totalAmount += this->_amount;
  _displayTimestamp(); 
  std::cout << "index:" << this->_accountIndex << ";"; 
  std::cout << "amount:" << this->_amount << ";created";
  std::cout << std::endl; 
}

Account::~Account(){
  
  _displayTimestamp(); 
  std::cout << "index:" << this->_accountIndex << ";"; 
  std::cout << "amount:" << this->_amount << ";closed";
  std::cout << std::endl; 
}

int	Account::getNbAccounts( void )
{
  return Account::_nbAccounts;
}

int	Account::getTotalAmount( void )
{
  return Account::_totalAmount;
}

int	Account::getNbDeposits( void )
{
  return Account::_totalNbDeposits;
}

int	Account::getNbWithdrawals( void )
{
  return Account::_totalNbWithdrawals;
}

void	Account::displayAccountsInfos( void ){
  
  Account::_displayTimestamp(); 
  std::cout << "accounts:" << Account::getNbAccounts() << ";";
  std::cout << "total:" << Account::getTotalAmount() << ";";
  std::cout << "deposits:" << Account::getNbDeposits() << ";";
  std::cout << "withdrawals:" << Account::getNbWithdrawals() << std::endl;
}

void	Account::makeDeposit( int deposit ){
  
  int p_amount = this->_amount;
  this->_amount += deposit;
  this->_nbDeposits++;
  Account::_totalNbDeposits++;
  Account::_totalAmount += deposit; 
  
  _displayTimestamp(); 
  std::cout << "index:" << this->_accountIndex << ";";
  std::cout << "p_amount:" << p_amount << ";";
  std::cout << "deposit:" << deposit << ";";
  std::cout << "amount:" << this->_amount << ";";
  std::cout << "nb_deposits:" << this->_nbDeposits;
  std::cout << std::endl;  
}

bool	Account::makeWithdrawal( int withdrawal )
{
  
  int p_amount = this->_amount;

  _displayTimestamp(); 
  std::cout << "index:" << this->_accountIndex << ";";
  std::cout << "p_amount:" << p_amount << ";";
  if (p_amount < withdrawal)
  {
    std::cout << "withdrawal:refused";
    std::cout << std::endl;
    return false;
  }
  else
  {
    this->_amount -= withdrawal;
    this->_nbWithdrawals++;
    Account::_totalNbWithdrawals++; 
    Account::_totalAmount -= withdrawal; 
    std::cout << "withdrawal:" << withdrawal << ";";
    std::cout << "amount:" << this->_amount << ";";
    std::cout << "nb_withdrawals:" << this->_nbWithdrawals;
    std::cout << std::endl;
    return true;
  }   
}

int		Account::checkAmount( void ) const
{
      return this->_amount;
}

void	Account::displayStatus( void ) const
{
  _displayTimestamp(); 
  std::cout << "index:" << this->_accountIndex << ";";
  std::cout << "amount:" << this->_amount << ";";
  std::cout << "deposits:" << this->_nbDeposits << ";";
  std::cout << "withdrawals:" << this->_nbWithdrawals;
  std::cout << std::endl;
}
    

void	Account::_displayTimestamp( void )
{  
  time_t  rawtime;
  struct tm *timeinfo;
  char compact[16];
  char buffer[20];
  int j = 0;
  
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer, 20, "%F_%T", timeinfo);
  
  for (size_t i = 0; i < strlen(buffer); i++)
  {
    if ((buffer[i] >= '0' && buffer[i] <= '9') || buffer[i] == '_')
    {
      compact[j] = buffer[i];
      j++;
    }
  }
  
  compact[j] = '\0';
  std::cout << "[" << compact << "]";
  std::cout << " ";
}