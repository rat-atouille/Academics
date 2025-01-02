import os
import torch
from torchvision import models, transforms
from PIL import Image
import numpy as np
from scipy.spatial.distance import pdist, squareform
import matplotlib.pyplot as plt
from sklearn.manifold import MDS
from torchvision.models import AlexNet_Weights

# Step 1: Load Pre-trained AlexNet and Extract Feature Maps
def load_alexnet():
    # Load pre-trained AlexNet with updated weights argument
    weights = AlexNet_Weights.DEFAULT
    model = models.alexnet(weights=weights)
    
    # Specify layers to extract activations
    layers = ['features.0', 'features.3', 'features.6', 'features.8', 'features.10', 'classifier.1', 'classifier.4']
    layer_outputs = {layer: [] for layer in layers}

    # Hook to extract intermediate outputs
    def get_activation(name):
        def hook(model, input, output):
            layer_outputs[name].append(output.flatten(start_dim=1).detach().numpy())
        return hook

    # Register hooks
    hooks = {
        'features.0': model.features[0].register_forward_hook(get_activation('features.0')),
        'features.3': model.features[3].register_forward_hook(get_activation('features.3')),
        'features.6': model.features[6].register_forward_hook(get_activation('features.6')),
        'features.8': model.features[8].register_forward_hook(get_activation('features.8')),
        'features.10': model.features[10].register_forward_hook(get_activation('features.10')),
        'classifier.1': model.classifier[1].register_forward_hook(get_activation('classifier.1')),
        'classifier.4': model.classifier[4].register_forward_hook(get_activation('classifier.4')),
    }

    return model, layers, layer_outputs

def preprocess_images(image_dir):
    # Define image transformations
    transform = transforms.Compose([
        transforms.Resize((224, 224)),
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
    ])

    # Load and preprocess images
    images = sorted(os.listdir(image_dir))
    inputs = []
    for img_name in images:
        img_path = os.path.join(image_dir, img_name)
        img = Image.open(img_path).convert('RGB')  # Convert to RGB in case of grayscale images
        inputs.append(transform(img).unsqueeze(0))  # Add batch dimension
    return inputs

def extract_activations(model, inputs, layers, layer_outputs):
    model.eval()  # Set model to evaluation mode
    with torch.no_grad():
        for img in inputs:
            model(img)  # Forward pass to populate activations

    # Flatten activations
    activations = {layer: np.concatenate(layer_outputs[layer], axis=0) for layer in layers}
    return activations

# Step 2: Create Representational Dissimilarity Matrix (RDM)
def compute_rdms(activations):
    rdms = {}
    for layer, activation in activations.items():
        rdm = squareform(pdist(activation, metric='euclidean'))
        rdms[layer] = rdm
    return rdms

# Step 3: Visualize RDM and MDS
def plot_rdm(rdms):
    for layer, rdm in rdms.items():
        plt.figure(figsize=(10, 8))
        plt.imshow(rdm, cmap='viridis')
        plt.title(f"RDM for {layer}")
        plt.colorbar()
        plt.show()

def plot_mds(rdms, labels):
    for layer, rdm in rdms.items():
        mds = MDS(n_components=2, dissimilarity='precomputed', random_state=42)
        coords = mds.fit_transform(rdm)
        plt.figure(figsize=(10, 8))
        for i, label in enumerate(np.unique(labels)):
            idx = np.where(labels == label)
            plt.scatter(coords[idx, 0], coords[idx, 1], label=label)
        plt.title(f"MDS for {layer}")
        plt.legend()
        plt.show()

# Main Script
if __name__ == "__main__":
    # Load AlexNet and set up hooks
    alexnet, layers, layer_outputs = load_alexnet()

    # Preprocess images
    image_dir = "images"
    inputs = preprocess_images(image_dir)

    # Extract activations
    activations = extract_activations(alexnet, inputs, layers, layer_outputs)

    # Compute RDMs
    rdms = compute_rdms(activations)

    # Define labels
    labels = np.array(["Animals"] * 28 + ["Objects"] * 36 + ["Scenes"] * 36 +
                      ["Human Activities"] * 24 + ["Faces"] * 32)

    # Plot RDMs
    plot_rdm(rdms)

    # Plot MDS
    plot_mds(rdms, labels)
