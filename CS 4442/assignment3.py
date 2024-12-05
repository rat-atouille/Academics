import numpy as np
import matplotlib.pyplot as plt

def create_gaussian_kernel(size, sigma):
    ax = np.linspace(-(size // 2), size // 2, size)
    xx, yy = np.meshgrid(ax, ax)
    kernel = np.exp(-(xx**2 + yy**2) / (2 * sigma**2))
    return kernel / np.sum(kernel)

def convolve(image, kernel):
    kernel = np.flipud(np.fliplr(kernel))
    output = np.zeros_like(image, dtype=float)
    pad_h, pad_w = kernel.shape[0] // 2, kernel.shape[1] // 2
    padded_image = np.pad(image, ((pad_h, pad_h), (pad_w, pad_w)), mode='reflect')
    for i in range(image.shape[0]):
        for j in range(image.shape[1]):
            region = padded_image[i:i + kernel.shape[0], j:j + kernel.shape[1]]
            output[i, j] = np.sum(region * kernel)
    return output

def sobel_filters():
    Sx = np.array([[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]])
    Sy = np.array([[-1, -2, -1], [0, 0, 0], [1, 2, 1]])
    return Sx, Sy

def edge_magnitude(Gx, Gy):
    return np.sqrt(Gx**2 + Gy**2)

def create_derivative_gaussian_kernel(size, sigma, axis='x'):
    ax = np.linspace(-(size // 2), size // 2, size)
    xx, yy = np.meshgrid(ax, ax)
    gaussian = np.exp(-(xx**2 + yy**2) / (2 * sigma**2))
    if axis == 'x':
        kernel = -(xx / (sigma**2)) * gaussian
    else:
        kernel = -(yy / (sigma**2)) * gaussian
    return kernel

def normalize_image(image):
    min_val = np.min(image)
    max_val = np.max(image)
    return (image - min_val) / (max_val - min_val)

def non_max_suppression(img, window_size=3):
    result = np.copy(img)
    pad = window_size // 2
    for i in range(pad, img.shape[0] - pad):
        for j in range(pad, img.shape[1] - pad):
            window = img[i-pad:i+pad+1, j-pad:j+pad+1]
            if img[i, j] != np.max(window):
                result[i, j] = 0
    return result

# Problem One - Part a
def plot_problem_one_a(image, smoothed_1, smoothed_2):
    plt.figure(figsize=(15, 5))
    plt.subplot(131)
    plt.title('Original Image')
    plt.imshow(image, cmap='gray')
    plt.axis('off')
    plt.subplot(132)
    plt.title('Gaussian Smoothing (σ=1)')
    plt.imshow(smoothed_1, cmap='gray')
    plt.axis('off')
    plt.subplot(133)
    plt.title('Gaussian Smoothing (σ=2)')
    plt.imshow(smoothed_2, cmap='gray')
    plt.axis('off')
    plt.tight_layout()
    plt.show()

# Problem One - Part b
def plot_problem_one_b(edge_map_sobel_1, edge_map_sobel_2):
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    plt.title('Sobel Edge Map (σ=1)')
    plt.imshow(normalize_image(edge_map_sobel_1), cmap='gray')
    plt.axis('off')
    plt.subplot(122)
    plt.title('Sobel Edge Map (σ=2)')
    plt.imshow(normalize_image(edge_map_sobel_2), cmap='gray')
    plt.axis('off')
    plt.tight_layout()
    plt.show()

# Problem One - Part c
def plot_problem_one_c(edge_map_dog_1, edge_map_dog_2):
    plt.figure(figsize=(10, 5))
    plt.subplot(121)
    plt.title('DoG Edge Map (σ=1)')
    plt.imshow(normalize_image(edge_map_dog_1), cmap='gray')
    plt.axis('off')
    plt.subplot(122)
    plt.title('DoG Edge Map (σ=2)')
    plt.imshow(normalize_image(edge_map_dog_2), cmap='gray')
    plt.axis('off')
    plt.tight_layout()
    plt.show()

# Problem One
def problem_one(image_path):
    print("Processing Problem 1: Edge Detection")
    image = plt.imread(image_path)
    if image.ndim == 3:
        image = np.mean(image, axis=2)
    image = normalize_image(image)
    
    # part a
    gaussian_kernel_1 = create_gaussian_kernel(5, sigma=1)
    gaussian_kernel_2 = create_gaussian_kernel(5, sigma=2)
    smoothed_1 = convolve(image, gaussian_kernel_1)
    smoothed_2 = convolve(image, gaussian_kernel_2)
    plot_problem_one_a(image, smoothed_1, smoothed_2)
    
    # part b
    Sx, Sy = sobel_filters()
    Gx_1 = convolve(smoothed_1, Sx)
    Gy_1 = convolve(smoothed_1, Sy)
    edge_map_sobel_1 = edge_magnitude(Gx_1, Gy_1)
    Gx_2 = convolve(smoothed_2, Sx)
    Gy_2 = convolve(smoothed_2, Sy)
    edge_map_sobel_2 = edge_magnitude(Gx_2, Gy_2)
    plot_problem_one_b(edge_map_sobel_1, edge_map_sobel_2)
    
    # part c
    dgx_1 = create_derivative_gaussian_kernel(5, sigma=1, axis='x')
    dgy_1 = create_derivative_gaussian_kernel(5, sigma=1, axis='y')
    dgx_2 = create_derivative_gaussian_kernel(5, sigma=2, axis='x')
    dgy_2 = create_derivative_gaussian_kernel(5, sigma=2, axis='y')
    Gx_dog_1 = convolve(image, dgx_1)
    Gy_dog_1 = convolve(image, dgy_1)
    edge_map_dog_1 = edge_magnitude(Gx_dog_1, Gy_dog_1)
    Gx_dog_2 = convolve(image, dgx_2)
    Gy_dog_2 = convolve(image, dgy_2)
    edge_map_dog_2 = edge_magnitude(Gx_dog_2, Gy_dog_2)
    plot_problem_one_c(edge_map_dog_1, edge_map_dog_2)

# Problem Two
def problem_two(image_path):
    print("\nProcessing Problem 2: Corner Detection")
    image = plt.imread(image_path)
    if image.ndim == 3:
        image = np.mean(image, axis=2)
    image = normalize_image(image)
    
    Sx, Sy = sobel_filters()
    Ix = convolve(image, Sx)
    Iy = convolve(image, Sy)
    Ixx = Ix * Ix
    Iyy = Iy * Iy
    Ixy = Ix * Iy
    window = create_gaussian_kernel(5, sigma=1)
    Sxx = convolve(Ixx, window)
    Syy = convolve(Iyy, window)
    Sxy = convolve(Ixy, window)
    
    k = 0.04
    det = (Sxx * Syy) - (Sxy ** 2)
    trace = Sxx + Syy
    R = det - k * (trace ** 2)
    
    threshold = 0.01 * np.max(R)
    R[R < threshold] = 0
    corners = non_max_suppression(R)
    corner_coords = np.where(corners > 0)
    
    plt.figure(figsize=(20, 5))
    plt.subplot(131)
    plt.title('Original Image')
    plt.imshow(image, cmap='gray')
    plt.axis('off')
    plt.subplot(132)
    plt.title('Corner Response Map')
    plt.imshow(normalize_image(R), cmap='jet')
    plt.colorbar()
    plt.axis('off')
    plt.subplot(133)
    plt.title('Detected Corners')
    plt.imshow(image, cmap='gray')
    plt.plot(corner_coords[1], corner_coords[0], 'r+', markersize=10)
    plt.axis('off')
    plt.tight_layout()
    plt.show()

# Main Execution
if __name__ == "__main__":
    image_path = 'image1.png' 
    try:
        problem_one(image_path)
        problem_two(image_path)
    except Exception as e:
        print(f"Error processing image")
