// This File is Part of the Vanadium Kern Game Engine.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include <kern/gfx/handles.hpp>
#include <kern/types/types.hpp>
#include <kern/exception/exception.hpp>

#include <vector>
#include <iostream>

#include <spdlog/logger.h>


namespace kern::gl
{
    template <typename Resource>
    struct ResourceSlot
    {
        std::unique_ptr<Resource> content;
        index_t generation;
        index_t index;

        wrap_hdl<Resource> create_handle()
        {
            return {.index = index, .generation = generation};
        }
    };

    template <typename Resource>
    class ResourceContainer
    {
        using hdl_t = wrap_hdl_t<Resource>;

        std::vector<ResourceSlot<Resource>> slots_{};

        spdlog::logger& logger_;

        // Push a new empty slot
        hdl_t new_empty_slot();

        // Return a new ResourceSlot, or re-use a free one
        hdl_t next_slot();

    public:
        explicit ResourceContainer(spdlog::logger& logger);

        /**
         * Returns <code>true</code> if <code>handle</code> points to an existing resource.<br/><br/>
         * <b>Note:</b> If the slot pointed to by the handle exists but is empty, this function
         * will return <code>false</code>.
         */
        bool is_valid_handle(const hdl_t& handle);

        ResourceSlot<Resource>& get_slot(const hdl_t& handle);
        const ResourceSlot<Resource>& get_slot(const hdl_t& handle) const;

        Resource& get_resource(const hdl_t& handle);
        const Resource& get_resource(const hdl_t& handle) const;

        void delete_resource(const hdl_t& handle);

        template <typename... Args>
        hdl_t add_resource(Args&&... args);
    };

    template <typename Resource>
    ResourceContainer<Resource>::ResourceContainer(spdlog::logger& logger)
        : logger_(logger)
    {
        logger_.debug("Creating resource container for {}.", rsrc_name_v<Resource>);
    }

    template <typename Resource>
    ResourceContainer<Resource>::hdl_t ResourceContainer<Resource>::new_empty_slot()
    {
        const ResourceSlot<Resource>& slot = slots_.emplace_back(nullptr, 1, slots_.size());
        return slot.create_handle();
    }

    template <typename Resource>
    ResourceContainer<Resource>::hdl_t ResourceContainer<Resource>::next_slot()
    {
        // Try to find an existing empty slot first
        for (std::size_t i = 0; i < slots_.size(); i++)
        {
            const ResourceSlot<Resource>& slot = slots_.at(i);

            if (slot.content != nullptr)
            {
                continue;
            }

            ++slot.generation;
            return slot.create_handle();
        }

        // There are no free slots. We need to create a new one
        return new_empty_slot();
    }

    template <typename Resource>
    bool ResourceContainer<Resource>::is_valid_handle(const hdl_t& handle)
    {
        try
        {
            const auto& slot = slots_.at(handle.index);
            return slot.generation == handle.generation && slot.content != nullptr;
        }
        catch (const std::out_of_range&)
        {
            return false;
        }
    }

    template <typename Resource>
    ResourceSlot<Resource>& ResourceContainer<Resource>::get_slot(const hdl_t& handle)
    {
        const auto index = handle.index;
        try
        {
            auto &slot = slots_.at(index);

            if (slot.generation != handle.generation)
            {
                throw exception::Exception(std::format(
                        "ResourceContainer Error: Attempted to retrieve a {} resource slot at index {} with a "
                        "mismatched handle. (Slot Generation: {}, Handle Generation: {})",
                        rsrc_name_v<Resource>, index, slot.generation, handle.generation)
                );
            }

            return slot;
        }
        catch (const std::out_of_range&)
        {
            throw exception::Exception(std::format(
                "ResourceContainer Error: Attempted to retrieve an out of bounds {} resource slot "
                "(Index: {}, Generation: {})",
                rsrc_name_v<Resource>, index, handle.generation
            ));
        }
    }

    template <typename Resource>
    const ResourceSlot<Resource>& ResourceContainer<Resource>::get_slot(const hdl_t& handle) const
    {
        return const_cast<ResourceContainer*>(*this)->get_slot(handle);
    }

    template <typename Resource>
    Resource& ResourceContainer<Resource>::get_resource(const hdl_t& handle)
    {
        auto& ptr = get_slot(handle).content;

        if (!ptr)
        {
            throw exception::Exception(std::format(
                "ResourceContainer Error: Attempted to retrieve a {} resource from empty slot "
                "(Index: {}, Generation: {})", rsrc_name_v<Resource>, handle.index, handle.generation
            ));
        }
        return *ptr;
    }

    template <typename Resource>
    const Resource& ResourceContainer<Resource>::get_resource(const hdl_t& handle) const
    {
        return const_cast<ResourceContainer*>(*this)->get_resource(handle);
    }

    template <typename Resource>
    void ResourceContainer<Resource>::delete_resource(const hdl_t& handle)
    {
        auto& slot = get_slot(handle);
        slot.content = nullptr;
    }

    template <typename Resource>
    template <typename... Args>
    ResourceContainer<Resource>::hdl_t ResourceContainer<Resource>::add_resource(Args&&... args)
    {
        auto [slot, index] = next_slot();

        exception::assert_or_throw(
            slot != nullptr,
            "ResourceManager: next_slot() returned a nullptr when trying to add resource"
        );

        slot->content = std::make_unique<Resource>(std::forward<Args>(args)...);
        return hdl_t{.index = index, .generation = slot->generation};
    }
}
