import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import KFold

# Load data
x_train = np.loadtxt('hw1xtr.dat')
y_train = np.loadtxt('hw1ytr.dat')
x_test = np.loadtxt('hw1xte.dat')
y_test = np.loadtxt('hw1yte.dat')

def get_poly_features(x):
    return np.column_stack([x**i for i in range(5)])  # 0 to 4

def fit_model(X, y, lambda_reg):
    n = X.shape[1]
    reg = lambda_reg * np.eye(n)
    reg[0,0] = 0  # Don't regularize bias term
    w = np.linalg.inv(X.T @ X + reg) @ X.T @ y
    return w

# Calculate MSE
def get_error(X, y, w):
    return np.mean((X @ w - y) ** 2)

# Setup
X_train = get_poly_features(x_train)
X_test = get_poly_features(x_test)
lambdas = [0.01, 0.1, 1, 10, 100, 1000, 10000]

train_errors = []
test_errors = []
all_weights = []

for lam in lambdas:
    w = fit_model(X_train, y_train, lam)
    train_errors.append(get_error(X_train, y_train, w))
    test_errors.append(get_error(X_test, y_test, w))
    all_weights.append(w)

plt.figure(figsize=(10, 5))
plt.semilogx(lambdas, train_errors, 'bo-', label='Train')
plt.semilogx(lambdas, test_errors, 'ro-', label='Test')
plt.xlabel('Lambda (log scale)')
plt.ylabel('Error')
plt.legend()
plt.title('Errors vs Lambda')
plt.show()

plt.figure(figsize=(10, 5))
all_weights = np.array(all_weights)
for i in range(5):
    plt.semilogx(lambdas, all_weights[:,i], 'o-', label=f'w{i}')
plt.xlabel('Lambda (log scale)')
plt.ylabel('Weight Value')
plt.legend()
plt.title('Weights vs Lambda')
plt.show()

cv_errors = []
kf = KFold(n_splits=5, shuffle=True, random_state=42)

for lam in lambdas:
    fold_errors = []
    for train_idx, val_idx in kf.split(x_train):
        # Split data
        X_fold = get_poly_features(x_train[train_idx])
        X_val = get_poly_features(x_train[val_idx])
        
        # Train and evaluate
        w = fit_model(X_fold, y_train[train_idx], lam)
        error = get_error(X_val, y_train[val_idx], w)
        fold_errors.append(error)
    
    cv_errors.append(np.mean(fold_errors))

plt.figure(figsize=(10, 5))
plt.semilogx(lambdas, cv_errors, 'go-', label='CV Error')
plt.xlabel('Lambda (log scale)')
plt.ylabel('Error')
plt.legend()
plt.title('Cross-Validation Error vs Lambda')
plt.show()

best_lambda = lambdas[np.argmin(cv_errors)]
best_w = fit_model(X_train, y_train, best_lambda)

plt.figure(figsize=(10, 5))
plt.scatter(x_test, y_test, c='g', label='Test Data')
x_plot = np.linspace(min(x_test), max(x_test), 100)
y_plot = get_poly_features(x_plot) @ best_w
plt.plot(x_plot, y_plot, 'r-', label=f'Best fit (λ={best_lambda})')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Final Model with Best Lambda')
plt.show()

print(f"Best lambda from CV: {best_lambda}")
print(f"Final test error: {get_error(X_test, y_test, best_w):.4f}")
