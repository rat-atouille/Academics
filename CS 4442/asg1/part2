## Assignment 1 
## Question 2

import numpy as np
import matplotlib.pyplot as plt

x_train = np.loadtxt('hw1xtr.dat')
y_train = np.loadtxt('hw1ytr.dat')
x_test = np.loadtxt('hw1xte.dat')
y_test = np.loadtxt('hw1yte.dat')

def plot_data():
    plt.figure(figsize=(12, 6))
    
    # training data
    plt.subplot(1, 2, 1)
    plt.scatter(x_train, y_train, color='blue', label='Training')
    plt.title('Training Data')
    plt.xlabel('x'), plt.ylabel('y')
    plt.legend()
    
    # test data
    plt.subplot(1, 2, 2)
    plt.scatter(x_test, y_test, color='green', label='Test')
    plt.title('Test Data')
    plt.xlabel('x'), plt.ylabel('y')
    plt.legend()
    
    plt.tight_layout()
    plt.show()

def fit_polynomial(degree):
    X_train_poly = np.column_stack([x_train**i for i in range(degree + 1)])
    X_test_poly = np.column_stack([x_test**i for i in range(degree + 1)])
    
    #  weights
    w = np.linalg.inv(X_train_poly.T @ X_train_poly) @ X_train_poly.T @ y_train
    
    # predictions
    train_pred = X_train_poly @ w
    test_pred = X_test_poly @ w
    
    # errors
    train_error = np.mean((train_pred - y_train) ** 2)
    test_error = np.mean((test_pred - y_test) ** 2)
    
    # results
    x_plot = np.linspace(min(x_train), max(x_train), 100)
    y_plot = sum(w[i] * x_plot**i for i in range(degree + 1))
    
    # Training plot
    plt.figure()
    plt.scatter(x_train, y_train, color='blue', label='Training')
    plt.plot(x_plot, y_plot, color='red', label=f'Degree {degree}')
    plt.title(f'Degree {degree} Polynomial (Training)')
    plt.legend()
    plt.show()
    
    # Test plot
    plt.figure()
    plt.scatter(x_test, y_test, color='green', label='Test')
    plt.plot(x_plot, y_plot, color='red', label=f'Degree {degree}')
    plt.title(f'Degree {degree} Polynomial (Test)')
    plt.legend()
    plt.show()
    
    return train_error, test_error

plot_data()

for degree in range(1, 5):
    train_error, test_error = fit_polynomial(degree)
    print(f"Degree {degree}:")
    print(f"Training error: {train_error:.4f}")
    print(f"Test error: {test_error:.4f}\n")
