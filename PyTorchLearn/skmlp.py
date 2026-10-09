

import mglearn.plots
import sklearn

from sklearn.model_selection import train_test_split
from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import StandardScaler

from data import make_two_moons

import matplotlib.pyplot as plt

def train_two_moons():
    features,labels = make_two_moons(n_samples = 200,noise = 0.15,random_state = 0)
    X_train, X_test, y_train, y_test = train_test_split (
        features,
        labels,
        stratify = labels,
        random_state = 42
    )

    scaler = StandardScaler()
    X_train = scaler.fit_transform(X_train)
    X_test = scaler.transform(X_test)

    mlp = MLPClassifier (
        solver='lbfgs',
        activation='tanh',
        random_state=0,
        hidden_layer_sizes=[10, 10],
        max_iter=1000
    )

    mlp.fit(X_train, y_train)
    print(f'Accuracy on train set: {mlp.score(X_train, y_train):.2f}')
    print(f'Accuracy on test set: {mlp.score(X_test, y_test):.2f}')

    mglearn.plots.plot_2d_separator(mlp,X_train,fill = True,alpha = .3)
    mglearn.discrete_scatter(X_train[:,0],X_train[:,1],y_train)
    plt.xlabel('Feature 0')
    plt.ylabel('Feature 1')

    plt.show()

if __name__ == '__main__':
    train_two_moons()