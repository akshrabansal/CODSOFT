import pandas as pd
import numpy as np
from sklearn.metrics.pairwise import cosine_similarity

# Sample dataset
data = {
    'user_id': [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4],
    'movie_id': [1, 2, 3, 1, 2, 4, 2, 3, 4, 1, 3],
    'rating': [5, 4, 1, 4, 5, 2, 5, 4, 4, 3, 5]
}

# Create DataFrame
df = pd.DataFrame(data)

# Create user-movie matrix
user_movie_matrix = df.pivot(index='user_id', columns='movie_id', values='rating').fillna(0)

# Compute cosine similarity between users
user_similarity = cosine_similarity(user_movie_matrix)
user_similarity_df = pd.DataFrame(user_similarity, index=user_movie_matrix.index, columns=user_movie_matrix.index)

def predict_ratings(user_id, user_movie_matrix, user_similarity_df):
    similar_users = user_similarity_df[user_id].drop(user_id).sort_values(ascending=False).index
    user_ratings = user_movie_matrix.loc[user_id]

    # For each movie, compute the weighted average rating from similar users
    predicted_ratings = {}
    for movie in user_movie_matrix.columns:
        if user_ratings[movie] == 0:  # Predict only for movies not rated by the user
            similar_users_ratings = user_movie_matrix.loc[similar_users, movie]
            similarities = user_similarity_df.loc[user_id, similar_users]
            predicted_rating = np.dot(similar_users_ratings, similarities) / similarities.sum()
            predicted_ratings[movie] = predicted_rating

    return predicted_ratings

def recommend_movies(predicted_ratings, top_n=3):
    recommended_movies = sorted(predicted_ratings.items(), key=lambda x: x[1], reverse=True)[:top_n]
    return [movie_id for movie_id, rating in recommended_movies]

# Predict ratings for user 1
predicted_ratings_user_1 = predict_ratings(1, user_movie_matrix, user_similarity_df)
# Recommend movies for user 1
recommended_movies_user_1 = recommend_movies(predicted_ratings_user_1)
print(f"Recommended movies for user 1: {recommended_movies_user_1}")
