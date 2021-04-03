#pragma once

#include "Core/Core.h"
#include "Core/Logger.h"

#include <cstdint>
#include <glad/glad.h>
#include <vector>
#include <initializer_list>

namespace Xeno
{
    class XENO_API VertexBuffer
    {
    public:
		class VertexBufferLayout
		{
		public:
			struct VertexBufferElement
			{
				std::string mName;
				int32_t mSize = 0;
				uint32_t mType = GL_FLOAT;
				bool mNormalized = false;
				size_t mOffset = 0;
			};

			VertexBufferLayout() = default;
			VertexBufferLayout(const std::initializer_list<VertexBufferElement>& elements) :
				mElements(elements)
			{
				mStride = 0;
				size_t offset = 0;

				for (auto& element : mElements)
				{
					element.mOffset = offset;
					offset += element.mSize;
					mStride += element.mSize;
				}
			}

			void PushElement(VertexBufferElement element)
			{
				element.mOffset = element.mSize + mElements.back().mOffset;
				mStride += element.mSize;

				mElements.emplace_back(element);
			}

			[[nodiscard]] uint32_t GetStride() const 
			{ 
				return mStride; 
			}

			[[nodiscard]] const std::vector<VertexBufferElement>& GetElements() const 
			{ 
				return mElements; 
			}

			std::vector<VertexBufferElement>::iterator begin() 
			{ 
				return mElements.begin(); 
			}

			std::vector<VertexBufferElement>::iterator end() 
			{
				return mElements.end();
			}

			std::vector<VertexBufferElement>::const_iterator begin() const 
			{ 
				return mElements.begin();
			}

			std::vector<VertexBufferElement>::const_iterator end() const 
			{ 
				return mElements.end(); 
			}

		private:
			std::vector<VertexBufferElement> mElements;
			int32_t mStride = 0;
		};

		VertexBuffer(uint32_t drawType = GL_STATIC_DRAW);
		explicit VertexBuffer(uint32_t size, uint32_t drawType = GL_STATIC_DRAW);
		explicit VertexBuffer(void* data, uint32_t size, uint32_t drawType = GL_STATIC_DRAW);
		~VertexBuffer();

        void Bind() const;
        void Unbind() const;

		void PushElement(const VertexBufferLayout::VertexBufferElement& element);

		void SetDataNew(const void* data, uint32_t size, uint32_t drawType = GL_STATIC_DRAW);
		void SetDataExisting(const void* data, uint32_t size) const;

		void SetLayout(const VertexBufferLayout& layout);
		[[nodiscard]] const VertexBufferLayout& GetLayout() const;

    private:
        uint32_t mObjectID;
        VertexBufferLayout mLayout;
		uint32_t mDrawType;
    };
}