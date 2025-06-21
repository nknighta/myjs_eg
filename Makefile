# コンパイラとオプション
CXX = g++
# -MMD -MPフラグはヘッダーファイルの依存関係を生成するために追加
CXXFLAGS = -std=c++17 -Wall -g -I. -MMD -MP

# ビルドディレクトリ
BUILD_DIR = build

# ソースファイル
SOURCES = main.cpp lexer.cpp perser.cpp ast.cpp token.cpp

# オブジェクトファイル（buildディレクトリ内に配置）
OBJECTS = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

# 依存関係ファイル（.dファイル）
DEPS = $(OBJECTS:.o=.d)

# 実行ファイル名
EXECUTABLE = $(BUILD_DIR)/simple_js_engine

# デフォルトターゲット
.PHONY: all
all: $(EXECUTABLE)

# 実行ファイルのリンク
$(EXECUTABLE): $(OBJECTS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# buildディレクトリ作成ルールをオブジェクトファイルの依存関係として設定 (Order-only)
$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	@echo "Creating build directory..."
	@-mkdir $(BUILD_DIR)

# 各ソースファイルをコンパイルするルール
$(BUILD_DIR)/%.o: %.cpp
	@echo "Compiling $< -> $@"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# クリーンアップ
.PHONY: clean
clean:
	@echo "Cleaning up..."
	@-rm -rf $(BUILD_DIR)

# 生成された依存関係ファイルをインクルード
-include $(DEPS)
