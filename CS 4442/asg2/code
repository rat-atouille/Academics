import numpy as np
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA

faces = np.loadtxt('faces.dat')

def display_face(face_vector, title="Face Image"):
    face_matrix = np.rot90(face_vector.reshape(64, 64), k=3)
    plt.figure(figsize=(5, 5))
    plt.imshow(face_matrix, cmap='grey')
    plt.title(title)
    plt.axis('on')
    plt.show()

## a)
display_face(faces[99], "100th Original Image")

## b)
mean_face = np.mean(faces, axis=0)
faces_centered = faces - mean_face
display_face(faces_centered[99], "100th Mean-centered Image")

## c)
cov_matrix = np.cov(faces_centered.T)
eigenvalues, eigenvectors = np.linalg.eigh(cov_matrix)
idx = np.argsort(eigenvalues)[::-1]
eigenvalues = eigenvalues[idx]
eigenvectors = eigenvectors[:, idx]

plt.figure(figsize=(10, 5))
plt.plot(eigenvalues[:100], 'b-', linewidth=2)
plt.title('Top 100 Eigenvalues')
plt.xlabel('Index')
plt.ylabel('Eigenvalue')
plt.grid(True)
plt.show()

## d)
for i in range(5):
    display_face(eigenvectors[:, i], f"Eigenvector {i+1}")

def reconstruct_face(face_vector, components):
    reconstruction = np.zeros_like(face_vector)
    for k in range(components):
        v_k = eigenvectors[:, k]
        reconstruction += np.dot(face_vector, v_k) * v_k
    return reconstruction

## e
components_to_use = [10, 100, 200, 399]
display_face(faces_centered[99], "Original Mean-centered Image")

for n_components in components_to_use:
    reconstructed = reconstruct_face(faces_centered[99], n_components)
    display_face(reconstructed, f"Reconstructed with {n_components} components")
    error = np.mean((faces_centered[99] - reconstructed) ** 2)
    print(f"Mean squared error with {n_components} components: {error:.6f}")
